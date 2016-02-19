#ifdef MATLAB

#include "main.h"
#include "mex.h"

/*
 * timestwoalt.c - example found in API guide
 *
 * use mxGetScalar to return the values of scalars instead of pointers
 * to copies of scalar variables.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2011 The MathWorks, Inc.
 */

/* $Revision: 1.6.6.1 $ */

int simplexDecisionLogic(REAL *state, int n, REAL* command, int m)
{
  //return state[0] * command[0];
}


double pendulum_control(double *x, double **kg, int currentController)
{
    return x[0] * kg[0][currentController] +
           x[2] * kg[1][currentController] +
           x[3] * kg[2][currentController] +
           x[4] * kg[3][currentController];
}


/*
 * Main entry point:
 * params: current state (1xn vector), complex cntl command (1xm vector)
 * returns: true iff we should use the complex controller
 */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] )
{
  int n, m;
  double* state;
  double* kg;
  double* command;
  double* output;

    /* Check arguments */

  if (nrhs != 2)
    mexErrMsgIdAndTxt( "MATLAB:test:invalidNumInputs",
            "Two input argument required.");

  if (nlhs > 1)
    mexErrMsgIdAndTxt( "MATLAB:test:maxlhs",
            "Too many output arguments.");

  n = mxGetM(prhs[0]);
  m = mxGetM(prhs[1]);

  if( mxIsComplex(prhs[0]) ||
      mxIsComplex(prhs[1]))
        mexErrMsgIdAndTxt("MATLAB:test:notDouble",
            "Input matricies must be type double.");

  if(mxGetN(prhs[0])!=1 )
    mexErrMsgIdAndTxt( "MATLAB:test:notColumnVector",
            "The first input (state) must be a column vector");

  if(mxGetN(prhs[1])!=1 )
    mexErrMsgIdAndTxt( "MATLAB:test:notColumnVector",
            "The second input (command) must be a column vector");

  state = mxGetPr(prhs[0]);
  kg = mxGetPr(prhs[1]);

  mexPrintf("n = %d, m = %d, first[1] = %f\n", n, m, state[1]);

  /* create a 1-by-1 matrix for the return argument */
  plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
  output = mxGetPr(plhs[0]);

  //*output = (double)simplexDecisionLogic(state, n, command, m);
  *output = (double)pendulum_control(state, kg, 0);
}

#endif
