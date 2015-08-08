#define _BSD_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <time.h>
#include <sys/time.h>

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

const uint64_t BILLION = 1000000000;
const uint64_t MILLION = 1000000;
const char* MEASURE_VOLTAGE = "MEAS:VOLT?";
const char* MEASURE_CURRENT = "MEAS:CURR?";
const char* HELLO = "*IDN?";

int psfd = -1;

uint64_t interval(struct timeval* start, struct timeval* end) {
  uint64_t elapsed = 0;
  if ((end->tv_usec - start->tv_usec)<0) {
    elapsed = (end->tv_sec - start->tv_sec - 1) * MILLION;
    elapsed += MILLION + end->tv_usec - start->tv_usec;
  } else {
    elapsed = (end->tv_sec - start->tv_sec) * MILLION;
    elapsed += end->tv_usec - start->tv_usec;
  }
  return elapsed;
}

double readCurrent() {

  const char* msg = MEASURE_CURRENT;
  const int msg_len = strlen(msg);

  char current[64];
  current[0] = '\0'; // clear current
  
  const ssize_t bytesWritten = write(psfd, msg, msg_len);
  if ( bytesWritten < 0 ) {
    perror("write");
  }
  
  const ssize_t bytesRead = read(psfd, current, sizeof(current));
  if ( bytesRead < 0 ) {
    printf("errno=%d sizeof(current)=%d\n", errno, sizeof(current));
    perror("read");
  }
  
  current[bytesRead-1] = '\0'; // response from power supply doesn't have a trailing NUL
  
  char* errPtr;
  double amps = strtod(current, &errPtr);
  if ( errPtr == current ) { // error occurred
    perror("strtod");
  }

  return amps;
}

uint64_t cpuStateTimes[2][10];
const int USER = 0;
const int NICE = 1;
const int SYSTEM = 2;
const int IDLE = 3;
const int IOWAIT = 4;
const int IRQ = 5;
const int SOFTIRQ = 6;
const int STEAL = 7;
const int GUEST = 8;
const int GUEST_NICE = 9;

int currentSlots = 0;

void printCpuStates(uint64_t arr[10]) {
  for (int i = 0; i < 10; i++) {
    printf("%llu ", arr[i]);
  }
  printf("\n");
}

void parseCpuStateTimes(char* times, uint64_t output[10]) {
  for (int i = 0; i < 10; i++) {
    char* endptr;
    errno = 0; // to be able to tell when strtoll() fails
    uint64_t t = strtoll(times, &endptr, 10);

    if ((errno == ERANGE && (t == LONG_MAX || t == LONG_MIN))
        || (errno != 0 && t == 0)) {
      perror("strtol");
      assert(0);
    }

    output[i] = t;
    //printf("parsed time: %llu\n", t);
    times = endptr;
  }
}

double computeCpuUtilization(uint64_t curr[10], uint64_t prev[10]) {
  // NB: we ignore GUEST and GUEST_NICE since we aren't in a virtualized environment
  // hat tip to http://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux for this code
  uint64_t PrevIdle = prev[IDLE] + prev[IOWAIT];
  uint64_t CurrIdle = curr[IDLE] + curr[IOWAIT];
  uint64_t PrevNonIdle = prev[USER] + prev[NICE] + prev[SYSTEM] + prev[IRQ] + prev[SOFTIRQ] + prev[STEAL];
  uint64_t CurrNonIdle = curr[USER] + curr[NICE] + curr[SYSTEM] + curr[IRQ] + curr[SOFTIRQ] + curr[STEAL];
  uint64_t PrevTotal = PrevIdle + PrevNonIdle;
  uint64_t CurrTotal = CurrIdle + CurrNonIdle;

  if (CurrTotal > PrevTotal) {
    double CPU_Percentage = ((CurrTotal-PrevTotal) - (CurrIdle-PrevIdle)) / (double) (CurrTotal-PrevTotal);
    return CPU_Percentage; 
  } else { // avoid divide-by-0
    return -1.0;
  }
}

double readCpuUtilization() {

    char statBuf[256];
    
    int cpufd = open("/proc/stat", O_RDONLY);
    assert( cpufd >= 0 );

    const ssize_t bytesRead = read(cpufd, statBuf, sizeof(statBuf)-1);
    if ( bytesRead < 0 ) {
      printf("errno=%d sizeof(statBuf)=%d\n", errno, sizeof(statBuf));
      perror("read cpufd");
    }

    statBuf[bytesRead] = '\0';
    //printf("statBuf: %s\n", statBuf);

    int rv = close(cpufd);
    if (rv < 0) {
      perror("close cpufd");
    }

    parseCpuStateTimes(statBuf+3/*skip "cpu" prefix*/, cpuStateTimes[currentSlots]);
    //printCpuStates(cpuStateTimes[currentSlots]);
    //printCpuStates(cpuStateTimes[!currentSlots]);
    double cpuUtil = computeCpuUtilization(cpuStateTimes[currentSlots], cpuStateTimes[!currentSlots]);
    currentSlots = !currentSlots;
    return cpuUtil;
}

int main(int argc, char* argv[]) {

  psfd = open("/dev/usbtmc0", O_RDWR);
  assert( psfd >= 0 );

  //int logfd = open("log.times", O_WRONLY | O_CREAT | O_APPEND);
  //assert( logfd >= 0 );

  struct timeval start, end;

  // fill in cpuStateTimes[currentSlot] for future comparison
  readCpuUtilization();

  //for (int i = 0; i < 10; i++) {
  while (1) {

    gettimeofday(&start, NULL);
    double amps = readCurrent();
    gettimeofday(&end, NULL);

    const uint64_t currentMeasurement_us = interval(&start, &end);

    gettimeofday(&start, NULL);
    double cpuUtil = readCpuUtilization();
    gettimeofday(&end, NULL);

    const uint64_t cpuMeasurement_us = interval(&start, &end);

    printf( "%f Amps, measurement took: %llu us\n", amps, currentMeasurement_us );
    printf( "%f cpu utilization, measurement took: %llu us\n", cpuUtil, cpuMeasurement_us );

    //printf("USER_HZ = %ld\n", sysconf(_SC_CLK_TCK));

    // NB: adjust this to change the sampling rate. Sampling too frequently leads to bogus CPU utilization.
    usleep( 1000 * 1000 );

  }

  int r = close(psfd);
  if (r < 0) {
    perror("close psfd");
  }

}
