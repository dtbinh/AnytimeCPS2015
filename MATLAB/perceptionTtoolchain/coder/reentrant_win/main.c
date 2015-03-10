#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "matrix_exp.h"
#include "matrix_exp_initialize.h"
#include "matrix_exp_terminate.h"
#include "rtwtypes.h"
#define NUMELEMENTS (160*160)

typedef struct {
    real_T in[NUMELEMENTS];
    real_T out[NUMELEMENTS];
    matrix_expStackData* spillData;
} IODATA;

/* The thread_function calls the matrix_exp function written in MATLAB */
DWORD WINAPI thread_function(PVOID dummyPtr) {
    IODATA *myIOData = (IODATA*)dummyPtr;
    matrix_exp_initialize();
    matrix_exp(myIOData->spillData, myIOData->in, myIOData->out);
    matrix_exp_terminate();
    return 0;
}

void main() {
  HANDLE thread1, thread2;
  IODATA data1;
  IODATA data2;
  int32_T i;
  
  /*Initializing data for passing to the 2 threads*/
  matrix_expStackData* sd1 = (matrix_expStackData*)calloc(1,sizeof(matrix_expStackData));
  matrix_expStackData* sd2 = (matrix_expStackData*)calloc(1,sizeof(matrix_expStackData));
  
  data1.spillData = sd1;
  data2.spillData = sd2;
  
  for (i=0;i<NUMELEMENTS;i++) {
      data1.in[i] = 1;
      data1.out[i] = 0;
      data2.in[i] = 1.1;
      data2.out[i] = 0;
  }
  
  /*Initializing the 2 threads and passing appropriate data to the thread functions*/
  printf("Starting thread 1...\n");
  thread1 = CreateThread(NULL , 0, thread_function, (PVOID) &data1, 0, NULL);
  if (thread1 == NULL){
	     perror( "Thread 1 creation failed.");
		   exit(EXIT_FAILURE);
  	}

  printf("Starting thread 2...\n");
  thread2 = CreateThread(NULL, 0, thread_function, (PVOID) &data2, 0, NULL);
  if (thread2 == NULL){
      perror( "Thread 2 creation failed.");
      exit(EXIT_FAILURE);
  }
  
  /*Wait for both the threads to finish execution*/
  if (WaitForSingleObject(thread1, INFINITE) != WAIT_OBJECT_0){
	     perror( "Thread 1 join failed.");
		  exit(EXIT_FAILURE);
  	}
   
  if (WaitForSingleObject(thread2, INFINITE) != WAIT_OBJECT_0){
		  perror( "Thread 2 join failed.");
		  exit(EXIT_FAILURE);
	  }  
  
  free(sd1);
  free(sd2);
  
  printf("Finished Execution!\n");
  exit(EXIT_SUCCESS);
  
}
