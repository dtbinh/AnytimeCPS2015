// Taylor notes
// 1) set c99 standard via this method: http://stackoverflow.com/questions/16224746/how-to-use-c11-to-program-the-arduino
// it's in a file called platform.txt that allows one to specify the options to the C compiler, etc.

/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */

#include "main.h"
#include "util.h"
#include "pendulum.h"
//#include <SoftwareSerial.h>

const long RV_UNSAFE = 0;
const long RV_LMI_SAFE = 1;
const long RV_SIM_SAFE = 2;
const long RV_RTREACH_SAFE = 3;


int runtimeMs;
long iters;
long count_unsafe;
long count_lmisafe;
long count_simsafe;
long count_rtsafe;

long x_iter;
long v_iter;
long theta_iter;
long omega_iter;

//SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Goodnight moon test!");

  // timer library for concurrent timing events: http://playground.arduino.cc/Code/Timer
  // http://arduino.cc/en/Tutorial/YunSerialTerminal

  unsigned long time;
  time = millis(); // http://arduino.cc/en/reference/millis
  //prints time since program started
  Serial.println(time);
  
  delay(5000);

  // // example call: ./rtreach_arm 100 -0.1 0.0 0.0 0.0
  // ./rtreach_arm 100 -0.1 0.4 0.0 0.0
  // int main( int argc, const char* argv[] )
//  const char* main_argv[] = {"100", "-0.1", "0.4", "0.0", "0.0"};
//  const char* main_argv[] = {"100", "-0.1", "1.9", "0.0", "0.0"};
  REAL startState[4];
  long x = milliseconds();
  int r;
  
  Serial.println("ms from rtreach milliseconds: ");
  x = milliseconds();
  Serial.println(x);
  
  Serial.println("ms from millis: ");
  Serial.println(millis());

  // wait a second so as not to send massive amounts of data
  
//  while (1) {

//    delay(1000);



//runtimeMs = 2500;
startState[0] = -0.1;
startState[1] = 0.1;
startState[2] = 0.0;
startState[3] = 0.0;
r = main_avr(runtimeMs, startState);






//const int num_samples = 2;
//const int num_samples = 5;
const int num_samples = 12;

//long runtimes[] = {2500,3000,3500,4000,4500,5000};

//long runtimes[] = {5,10};

// not much gain between 3000, 5000, and 10000, at least for large sample points
//long runtimes[] = {3000,6000};
long runtimes[] = {100,500,1000,20};
//long runtimes[] = {2000,4500,6000};
//long runtimes[] = {5000};
//long runtimes[] = {10000};

int rt_size = sizeof(runtimes)/sizeof(runtimes[0]);

#if 1
REAL x_min = -1.25;
REAL x_max = 1.25;

REAL v_min = -1.2;
REAL v_max = 1.2;

REAL theta_min = -0.34906585;//radians(-20);
REAL theta_max = 0.34906585;//radians(20);

REAL omega_min = -0.523598776; //radians(-30);
REAL omega_max = 0.523598776; //radians(30);
#else
REAL x_min = -0.125;
REAL x_max = 0.125;

REAL v_min = -0.12;
REAL v_max = 1.2;

REAL theta_min = -0.034906585;//radians(-20);
REAL theta_max = 0.034906585;//radians(20);

REAL omega_min = -0.0523598776; //radians(-30);
REAL omega_max = 0.0523598776; //radians(30);
#endif

// different ICs
#if 1
REAL x_start = x_min;
REAL v_start = v_min;
#else
// restarting from trace
REAL x_start = 0.1388888888888888888888888888889; 

REAL v_start = 0.93333333333333333333333333333336;
#endif

REAL x_step = (x_max - x_min) / (num_samples - 1);
REAL v_step = (v_max - v_min) / (num_samples - 1);
REAL theta_step = (theta_max - theta_min) / (num_samples - 1);
REAL omega_step = (omega_max - omega_min) / (num_samples - 1);

if (((x_max - x_min) / x_step) != num_samples) {
  Serial.println("ERROR: x step and samples mismatch");
}
if (((v_max - v_min) / v_step) != num_samples) {
  Serial.println("ERROR: v step and samples mismatch");
}
if (((theta_max - theta_min) / theta_step) != num_samples) {
  Serial.println("ERROR: theta step and samples mismatch");
}
if (((omega_max - omega_min) / omega_step) != num_samples) {
  Serial.println("ERROR: omega step and samples mismatch");
}

REAL x_vals[num_samples];
REAL v_vals[num_samples];
REAL theta_vals[num_samples];
REAL omega_vals[num_samples];

for (int i = 0; i < num_samples; i++) {
  x_vals[i] = x_min + i * x_step;
  v_vals[i] = v_min + i * v_step;
  theta_vals[i] = theta_min + i * theta_step;
  omega_vals[i] = omega_min + i * omega_step;
}

#if 1
Serial.println("x step");
Serial.println(x_step, HEX);
Serial.println("v step");
Serial.println(v_step, HEX);
Serial.println("theta step");
Serial.println(theta_step, HEX);
Serial.println("omega step");
Serial.println(omega_step, HEX);

Serial.println("");
#endif


#define RUN_SCENARIOS 1 // run rtreach or not?


/*
x
0.14
v
0.93
runtime
3000
total
5220
unsafe
2602
lmi
602
simsafe
1798
rtsafe
218
*/

      for (int i_rt = 0; i_rt < rt_size; i_rt++) {
        #if 1
	iters = 0;
	count_unsafe = 0;
	count_lmisafe = 0;
	count_simsafe = 0;
	count_rtsafe = 0;
        #else
	iters = 5220;
	count_unsafe = 2602;
	count_lmisafe = 602;
	count_simsafe = 1798;
	count_rtsafe = 218;
        #endif
        runtimeMs = runtimes[i_rt];
        
        Serial.println("STARTING runtime");
        Serial.println(runtimeMs);
        
        x_iter = 0;
//	for (REAL x = x_start; x < x_max; x += x_step) {
        while (x_iter < num_samples) {
          REAL x = x_vals[x_iter];
//          Serial.println("next x");
//          Serial.println(x);
          v_iter = 0;
          //for (REAL v = v_start; v < v_max; v += v_step) {
          while (v_iter < num_samples) {
            REAL v = v_vals[v_iter];
            // print state here:
            // print points here, so we can restart using these as initial values
            // will offset printing too frequently (~1 every 13*13 iterations) and not being able to stop/restart

        Serial.println("iters");
        Serial.println(iters);
        Serial.println("x");
//        Serial.println(x);
//        Serial.println(double2str(x));
//        Serial.println(x, 6); // 6 digits
        Serial.println(x, HEX); // all digits
        //send_float(x);
        Serial.println("v");
        Serial.println(v, HEX); // other states can just be set normally, as they're iterated through each time, so don't print
        //send_float(v);
            
        printResults();
        theta_iter = 0;
//        for (REAL theta = theta_min; theta < theta_max; theta += theta_step) {
          while (theta_iter < num_samples) {
            REAL theta = theta_vals[theta_iter];
          omega_iter = 0;
//          for (REAL omega = omega_min; omega < omega_max; omega += omega_step) {
        while (omega_iter < num_samples) {
          REAL omega = omega_vals[omega_iter];
/*					# rtreach(rt, state(1), state(2), state(3), state(4)) % this is the right order, rtreach(runtime, x, v, theta, omega)
					# call shell script: http://stackoverflow.com/questions/3777301/how-to-call-a-shell-script-from-python-code
					rtreach_call_args = ['./rtreach_arm', str(rt), str(x), str(v), str(theta), str(omega)];
					if DEBUG:
						print rtreach_call_args
					#subprocess.Popen('echo $PWD', shell=True)
					p = subprocess.Popen(rtreach_call_args, stdout=None, stderr=None, shell=False);
					#subprocess.Popen('./rtreach_arm'); # works with no args
					retval = p.wait(); # wait for process to complete (to avoid starting lots of processes and messing up timing, etc.)
					if DEBUG:
						print "rtreach: " + str( retval )
*/

                  // reset timer crap (default linux/windows version assumes 1 process call, so these would be unset)
                  initialized = false;
                  startSec = 0;

                  startState[0] = x;
                  startState[1] = v;
                  startState[2] = theta;
                  startState[3] = omega;
                  
                  // print state values
                  #if 0 // debug, check state values
                  Serial.println("x");
                  Serial.println(x, HEX);
                  Serial.println("v");
                  Serial.println(v, HEX);
                  Serial.println("theta");
                  Serial.println(theta, HEX);
                  Serial.println("omega");
                  Serial.println(omega, HEX);
                  #endif
                  
#ifdef RUN_SCENARIOS
                  r = main_avr(runtimeMs, startState);
#endif
                  //Serial.println("reach done");
                  //Serial.println(r);
//                  Serial.println("");

#if 0
                  Serial.println("milliseconds: ");
                  Serial.println(milliseconds());
                  Serial.println(iters);
#endif


// TODO: add planar version for printing plots (will not take long to run, so do later)
// step 1: fix say theta and omega (or x and v for that scenario)
// step 2: entire PRINT message will be vector (not enough memory to store entire result)
//         therefore, print something like a vector so we can easily import to matlab for plotting
//         example (will double check first):
//         res x    v;
//         0   0.12 0.123;
//         1   0.0  0.05;
// where res is the rtreach result (return code for classification, and x and v values are the state points)
// using this, we can just copy / paste the serial output (serving as buffer) into matlab to plot using e.g., scatter
                  
                                        if (r == RV_UNSAFE) {
                                          count_unsafe = count_unsafe + 1;
                                        }
                                        else if (r == RV_LMI_SAFE) {
                                          count_lmisafe = count_lmisafe + 1;
                                        }
					else if (r == RV_SIM_SAFE) {
                                          count_simsafe = count_simsafe + 1;
                                        }
					else if (r == RV_RTREACH_SAFE) {
                                          count_rtsafe = count_rtsafe + 1;
                                        }


					iters = iters + 1;


              omega_iter += 1;
              } // omega

              if (omega_iter != num_samples) {
                Serial.println("ERROR: omega state iteration does not match samples");
              }
              
              theta_iter += 1;
            } // theta
            
              if (theta_iter != num_samples) {
                Serial.println("ERROR: theta state iteration does not match samples");
              }
            
          v_iter += 1;
          } // v
          
              if (v_iter != num_samples) {
                Serial.println("ERROR: v state iteration does not match samples");
              }

          
          x_iter += 1;
        } // x
        
              if (x_iter != num_samples) {
                Serial.println("ERROR: x state iteration does not match samples");
              }
#if 0 // debug for iteration numbers not matching
              Serial.print("x: ");
              Serial.print(x_iter);
              Serial.print(" v: ");
              Serial.print(v_iter);
              Serial.print(" t: ");
              Serial.print(theta_iter);
              Serial.print(" o: ");
              Serial.print(omega_iter);
#endif
        
        printResults();
        /*
        Serial.println("runtime");
        Serial.println(runtimeMs);
        Serial.println("total");
        Serial.println(iters);
        Serial.println("unsafe");
        Serial.println(count_unsafe);
        Serial.println("lmi");
        Serial.println(count_lmisafe);
        Serial.println("simsafe");
        Serial.println(count_simsafe);
        Serial.println("rtsafe");
        Serial.println(count_rtsafe);*/
      } // rt end
      Serial.println("TOTALLY DONE");
      
      if (iters != num_samples*num_samples*num_samples*num_samples) {
        Serial.println("ERROR: total iterations does not match samples^4");
      }
/*
	print os.linesep
	print "runtime: " + str( rt )
	print "total iter: " + str( iters )
	print "unsafe: " + str( count_unsafe )
	print "lmisafe: " + str( count_lmisafe )
	print "simsafe: " + str( count_simsafe )
	print "rtsafe: " + str( count_rtsafe )

	per_unsafe = count_unsafe / float(iters);
	per_lmisafe = count_lmisafe / float(iters);
	per_simsafe = count_simsafe / float(iters);
	per_rtsafe = count_rtsafe / float(iters);

	if count_lmisafe == 0:
		count_lmisafe = 1;

	per_improve = (count_rtsafe + count_lmisafe) / float(count_lmisafe);

	print "percent unsafe: " + str( per_unsafe )
	print "percent simsafe: " + str( per_simsafe )
	print "percent rtsafe: " + str( per_rtsafe )

#\textbf{Runtime (ms)} & \textbf{LMI} & \textbf{RealTime} & \textbf{Sim} & \textbf{Unrecov} & \textbf{Improve}\tabularnewline
#	5 & 5473  & 6180  & 1376  & 37596  & 213\% \tabularnewline
	print "TABLE ENTRY: "
	print str( rt ) + ' & ' + str( count_lmisafe ) + ' & ' + str( count_rtsafe ) + ' & ' + str( count_simsafe ) + ' & ' + str( count_unsafe ) + ' & ' + str( per_improve ) + " \\\\ "
*/








//main_avr(6, main_argv);
  
//  Serial.println("reach done");
//  Serial.println(r);

//    i = i + 1;
//  }

  // set the data rate for the SoftwareSerial port
  //mySerial.begin(4800);
  //mySerial.println("Hello, world?");
}

void loop() // run over and over
{
/*  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
    */
}

/*
// not needed, can use Serial.print(f,HEX) to print all digits
// details here: http://arduino.cc/en/Serial/Print
// http://stackoverflow.com/questions/3270967/how-to-send-float-over-serial
char *
double2str( double num ) {
    static char retnum[21];       // Enough for 20 digits plus NUL from a 64-bit double.
    sprintf( retnum, "%d", num );
    return retnum;
}
*/

/*void send_float (double arg)
{
  // get access to the float as a byte-array:
  byte * data = (byte *) &arg; 

  // write the data to the serial
  Serial.write (data, sizeof (arg));
}*/

void printResults() {
  Serial.println();
  Serial.println("RESULTS SO FAR");
  Serial.println("total execution time (ms)");
  Serial.println(millis());
  Serial.println("time per iteration (ms per)");
  Serial.println(millis() / iters);
  Serial.println("runtime limit");
  Serial.println(runtimeMs);
  Serial.println("total");
  Serial.println(iters);
  Serial.println("unsafe");
  Serial.println(count_unsafe);
  Serial.println("lmi");
  Serial.println(count_lmisafe);
  Serial.println("simsafe");
  Serial.println(count_simsafe);
  Serial.println("rtsafe");
  Serial.println(count_rtsafe);
}
