#include "hidapi.h"

#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>

// TODO: doesn't work if SmartPower is already on *and* recording.

// * Must turn on SmartPower, then run program, then enable recording (manually).
// * Requires libudev-dev on Linux
// * Requires root permissions on Linux

#define REQUEST_DATA        0x37
#define REQUEST_STARTSTOP   0x80
#define REQUEST_STATUS      0x81
#define REQUEST_ONOFF       0x82
#define REQUEST_VERSION     0x83

typedef unsigned char bool_t;
#define TRUE 1
#define FALSE 0

bool_t isConnected = FALSE;
bool_t onOffStatus = FALSE;
bool_t startStopStatus = FALSE;
bool_t toggleStartStop = FALSE;
bool_t toggleOnOff = FALSE;

bool_t skip = FALSE;
int lastCommand = 0;
int count = 0;

hid_device *device = NULL;
FILE* logFile = NULL;

#define MAX_STR 65
unsigned char buf[MAX_STR];
unsigned char buf2[MAX_STR];

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); } while (0)

useconds_t PollUSB();
void CloseDevice();
void OpenDevice();

void printData(unsigned char* b) {
  char* str = (char*) b;
  // characters in str are of the form:
  // 7?5.250V  1.298 A 6.828W  0.000W?X?%2?????2???銚	????,???
  fprintf(logFile, "%.5sV %.5sA %.6sW %.7sWh\n", &str[2], &str[10], &str[17], &str[24]);
  fflush(logFile);
}

void CloseDevice() {
    hid_close(device);
    device = NULL;
    isConnected = FALSE;
    toggleOnOff = FALSE;
    toggleStartStop = FALSE;
    //hid_comm_status_update(isConnected, onOffStatus, startStopStatus);
    
    printData(buf);
}

// static void handler(int sig, siginfo_t *si, void *uc) {
//   /* Note: calling printf() from a signal handler is not
//      strictly correct, since printf() is not async-signal-safe;
//      see signal(7) */
//   signal(sig, SIG_IGN);
//   PollUSB();
// }

useconds_t PollUSB() {
    buf[0] = 0x00;
    useconds_t sleeptime = 100 * 1000;

    if (isConnected == FALSE) {
      OpenDevice();
      return sleeptime;
    }
    
    assert(device != NULL);

    if (toggleStartStop == TRUE) {
      toggleStartStop = FALSE;
      
      unsigned char cmd[MAX_STR] = {0x00,};
      cmd[1] = REQUEST_STARTSTOP;
            
      if (hid_write(device, cmd, sizeof(cmd)) == -1) {
        fprintf(stderr, "error starting device\n");
        CloseDevice();
        return sleeptime;
      }
    }

    if (toggleOnOff == TRUE) {
      toggleOnOff = FALSE;

      unsigned char cmd[MAX_STR] = {0x00,};
      cmd[1] = REQUEST_ONOFF;
            
      if (hid_write(device, cmd, sizeof(cmd)) == -1) {
        fprintf(stderr, "error turning on device\n");
        CloseDevice();
        return sleeptime;
      }
    }
        
    lastCommand = buf[1];

    if (!skip) {
      if (hid_write(device, buf, sizeof(buf)) == -1) {
        fprintf(stderr, "error not skipping\n");
        CloseDevice();
        return sleeptime;
      }
    }

    usleep(10);

    if (hid_read(device, buf, sizeof(buf)) == -1) {
      fprintf(stderr, "error reading\n");
      CloseDevice();
      return sleeptime;
    }
        
    if (buf[0] != lastCommand) {
      skip = TRUE;
    } else {
      if (buf[0] == REQUEST_VERSION) {
        //hid_comm_version_update(buf); // TODO
        buf[1] = REQUEST_STATUS;
        skip = FALSE;
        sleeptime = 100 * 1000;
        count = 0;
        memset(buf2, 0x00, MAX_STR);
      } else if (buf[0] == REQUEST_DATA) {
        buf[1] = REQUEST_STATUS;
        memcpy(buf2, buf, MAX_STR);
      } else if (buf[0] == REQUEST_STATUS) {
        startStopStatus = (buf[1] == 0x01);
        onOffStatus = (buf[2] == 0x01);
        if (count == 9) {
          buf[1] = REQUEST_STATUS;
        } else {
          buf[1] = REQUEST_DATA;
        }
        //hid_comm_status_update(isConnected, onOffStatus, startStopStatus);
        count = 0;
      } else {
        if (lastCommand == REQUEST_STATUS) {
          buf[1] = REQUEST_DATA;
        } else {
          buf[1] = REQUEST_STATUS;
        }
      }
      skip = FALSE;
    }

    printData(buf2);
    count++;
    
    return sleeptime;
}

void OpenDevice() {
  buf[0] = 0x00;
  device = hid_open(0x04d8, 0x003f, NULL);
  
  if (device) {
    memset((void*)&buf[2], 0x00, sizeof(buf) - 2);
    isConnected = TRUE;
    hid_set_nonblocking(device, TRUE);
    
    buf[1] = REQUEST_VERSION;
    
    lastCommand = buf[1];
    
    if (hid_write(device, buf, sizeof(buf)) == -1) {
      fprintf(stderr, "[Open] error writing to device\n");
      CloseDevice();
      return;
    }
    
    if (hid_read(device, buf, sizeof(buf)) == -1) {
      fprintf(stderr, "[Open] error reading from device\n");
      CloseDevice();
      return;
    }
  } else {
    fprintf(stderr, "[Open] failed opening device\n");
  }
}

void* pollingThread(void* _) {
  while (TRUE) {
    useconds_t sleeptime = PollUSB();
    usleep(sleeptime);
  }
}

int main(int argc, char** argv) {

  if (argc != 2) {
    fprintf(stderr, "usage: %s output-file\n", argv[0]);
    return 1;
  }

  logFile = fopen(argv[1], "w+");
  
  // Enumerate and print the HID devices on the system
  struct hid_device_info *devs, *cur_dev;
  
  devs = hid_enumerate(0x0, 0x0);
  cur_dev = devs;
  while (cur_dev) {
    fprintf(logFile, "Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls\n",
           cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
    fprintf(logFile, "  Manufacturer: %ls\n", cur_dev->manufacturer_string);
    fprintf(logFile, "  Product:      %ls\n", cur_dev->product_string);
    fprintf(logFile, "\n");
    cur_dev = cur_dev->next;
  }
  hid_free_enumeration(devs);

  pthread_t thread;
  pthread_create(&thread, NULL, pollingThread, NULL);

  char c = ' ';
  while (TRUE) {
    
    scanf("%c", &c);
    switch (c) {
    case 'o':
      toggleOnOff = TRUE;
      break;
    case 's':
      toggleStartStop = TRUE;
      break;
      //default:
      //printf("Invalid input character.\n");
    }
    
  }

  return 0;
}
