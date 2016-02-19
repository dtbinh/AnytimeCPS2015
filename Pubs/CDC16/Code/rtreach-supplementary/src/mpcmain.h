// ./rtreach maxrunTime reachHorizon x0[0] x0[1] x0[2] x0[3]
// example call: ./rtreach 100 -0.1 0.0 0.0 1.1
// example matlab call: rtreach(100, -0.1, 0.0, 0.0, 1.1)
// Unsafe set is hard-coded in intermediateState()
// Recoverable region is hard-coded in finalState()
// initial point of reachability computation is input to this function
//
// state = {pos, vel, angle, angular_vel}
// from startState = {-0.1, vel, 0, 0};
// set velocity to 0.6 for a recoverable state inside the ellipse
// set velocity to 0.7 for a recoverable state slightly outside of the ellipse
// set velocity to 0.8 for a recoverable state outside of the ellipse
// set velocity to 0.9 for an unrecoverable state


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "car.h"

#ifdef MATLAB
// mxArray: see: http://www.mathworks.com/help/matlab/apiref/mxarray.html
#include "matrix.h"
#endif

const int state_n = 4; // state dimension


#if defined(MATLAB)
int main(int runtimeMs, REAL* startState)
{
#elif defined(ARDUINO)
// trying name change, linker problems as main already exists
//int main_avr( int argc, const char* argv[] )
int main_avr( int runtimeMs, REAL* startState)
{
#else
int main( int argc, const char* argv[] )
{
DEBUG_PRINT("started!\n\r");
            
int runtimeMs = 0;
int reachHorizon = 2;
REAL startState[state_n] = {0.0, 0.0, 0.0, 0.0};
DEBUG_PRINT("Argc: %d\n\r", argc);
            
if (argc < 7) {
   printf("Error: not enough input arguments!\n\r");
   return 0;
}
else {
    runtimeMs = atoi(argv[1]);
    reachHorizon = atoi(argv[2]);
    /*
     REAL initSet[state_n][2];
    REAL lowerbound;REAL upperbound;
    FILE *fp;
    fp = fopen("initset.txt", "r");
    int r = 0;
    while (fscanf(fp, "%f %f", &lowerbound, &upperbound) == 2) {
        initSet[r][0] = lowerbound;
        initSet[r][1] = upperbound;
        DEBUG_PRINT("Bounds = [%f , %f]\n", lowerbound, upperbound);
        r++;
    }
    fclose(fp);
     */
}
#endif // linux
            
            
#ifdef DEBUG
#ifdef MATLAB
            mexPrintf("runtime = %d\n", runtimeMs);
            mexPrintf("x[0] = %f\nx[1] = %f\nx[2] = %f\nx[3] = %f\n", startState[0], startState[1], startState[2], startState[3]);
#endif
#endif
            
            
            DEBUG_PRINT("potential of start state = %f\n",
                        potential(startState[0], startState[1], startState[2], startState[3]));
            //-0.1 0.0 0.0 1.1
            bool safe;
    
            REAL initSet[state_n][2] = {
                {-0.12, -0.95},
                {-0.05, 0.05},
                {-0.05, 0.05},
                {1.0, 1.2}
            };
            int startMs = milliseconds();
            DEBUG_PRINT("Runtime: %d ms, Reach horizon = %d ms, startMs=%d ms\n\rx_0[0]: %f\n\rx_0[1]: %f\n\rx_0[2]: %f\n\rx_0[3]: %f\n\r",
                        runtimeMs, reachHorizon, startMs,
                        startState[0], startState[1], startState[2], startState[3]);

            safe = runReachability(initSet, reachHorizon, runtimeMs, startMs);
            
            DEBUG_PRINT("done, result = %s\n", safe ? "safe" : "unsafe");
            
            // http://www.mathworks.com/help/matlab/apiref/mexprintf.html
#ifdef DEBUG
#ifdef MATLAB
            mexPrintf("done, result = %s\n", safe ? "safe" : "unsafe"); // TODO: convert to macro to call either printf or mexPrintf
#endif
#endif
            
            return safe;
        }
        
#ifdef MATLAB
        /**
         * Main entry point: calls main(), but is the actual first function called when executing inside Matlab
         *
         */
        void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
        {
            int i;
            
#ifdef DEBUG
            mexPrintf("nlhs: %d\n", nlhs);
            mexPrintf("nrhs: %d\n", nrhs);
#endif
            
            // example: edit([matlabroot '/extern/examples/mex/mexfunction.c']);
            
            // input example: http://www.mathworks.com/help/matlab/matlab_external/standalone-example.html
#ifdef DEBUG
            for (i=0; i<nrhs; i++)  {
                mexPrintf("\n\tInput Arg %i is of type:\t%s ",i,mxGetClassName(prhs[i]));
                mexPrintf("test: %f\n", mxGetScalar(prhs[i]));
            }
#endif
            
            REAL startState[4] = {mxGetScalar(prhs[1]), mxGetScalar(prhs[2]), mxGetScalar(prhs[3]), mxGetScalar(prhs[4])};
            
            bool result = 0;
            
            if (nrhs == 5) // TODO: make nicer, assumes set up for pendulum
            {
                result = main(mxGetScalar(prhs[0]), startState);
            }
            
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            
            REAL * output;
            
            output = mxGetPr(plhs[0]);
            
            *output = result;
            return;
        }
#endif
        
