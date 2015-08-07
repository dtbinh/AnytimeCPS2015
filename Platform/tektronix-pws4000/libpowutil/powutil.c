#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//#include <time.h>
#include <sys/time.h>

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

const uint64_t BILLION = 1000000000;
const uint64_t MILLION = 1000000;
const char* MEASURE_CURRENT = "MEAS:CURR?";
const char* HELLO = "*IDN?";

uint64_t subtractTimeval(struct timeval* start, struct timeval* end) {
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


int main(int argc, char* argv[]) {

  int devfd = open("/dev/usbtmc0", O_RDWR);
  assert( devfd >= 0 );
  
  //int logfd = open("log.times", O_WRONLY | O_CREAT | O_APPEND);
  //assert( logfd >= 0 );


  struct timeval start, current;

  for (int i = 0; i < 20; i++) {
    char result[64];
    result[0] = '\0'; // clear result

    gettimeofday(&start, NULL);

    ssize_t bytesWritten = write(devfd, MEASURE_CURRENT, strlen(MEASURE_CURRENT));
    if ( bytesWritten < 0 ) {
      perror("write");
    } else {
      //printf("wrote %d bytes\n", bytesWritten);
    }

    ssize_t bytesRead = read(devfd, result, sizeof(result));
    if ( bytesRead < 0 ) {
      printf("errno=%d sizeof(result)=%d\n", errno, sizeof(result));
      perror("read");
    }

    gettimeofday(&current, NULL);

    uint64_t us = subtractTimeval(&start, &current);
    result[bytesRead] = '\0'; // response from power supply doesn't have a trailing NUL
    printf( "%s Amps, read %d bytes, measurement took: %llu us\n", result, bytesRead, us );

  }

  int r = close(devfd);
  if (r < 0) {
    perror("close");
  }

}
