/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_alt_getCoefficientsVector_genable_mex.c
 *
 * Code generation for function '_coder_alt_getCoefficientsVector_genable_mex'
 *
 */

/* Include files */
#include "alt_getCoefficientsVector_genable.h"
#include "_coder_alt_getCoefficientsVector_genable_mex.h"
#include "alt_getCoefficientsVector_genable_terminate.h"
#include "_coder_alt_getCoefficientsVector_genable_api.h"
#include "alt_getCoefficientsVector_genable_initialize.h"
#include "alt_getCoefficientsVector_genable_data.h"

/* Function Declarations */
static void c_alt_getCoefficientsVector_gen(int32_T nlhs, mxArray *plhs[2],
  int32_T nrhs, const mxArray *prhs[9]);

/* Function Definitions */
static void c_alt_getCoefficientsVector_gen(int32_T nlhs, mxArray *plhs[2],
  int32_T nrhs, const mxArray *prhs[9])
{
  int32_T n;
  const mxArray *inputs[9];
  const mxArray *outputs[2];
  int32_T b_nlhs;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 9) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 9, 4,
                        33, "alt_getCoefficientsVector_genable");
  }

  if (nlhs > 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 33,
                        "alt_getCoefficientsVector_genable");
  }

  /* Temporary copy for mex inputs. */
  for (n = 0; n < nrhs; n++) {
    inputs[n] = prhs[n];
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(&st);
    }
  }

  /* Call the function. */
  alt_getCoefficientsVector_genable_api(inputs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  alt_getCoefficientsVector_genable_terminate();
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(alt_getCoefficientsVector_genable_atexit);

  /* Initialize the memory manager. */
  /* Module initialization. */
  alt_getCoefficientsVector_genable_initialize();

  /* Dispatch the entry-point. */
  c_alt_getCoefficientsVector_gen(nlhs, plhs, nrhs, prhs);
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_alt_getCoefficientsVector_genable_mex.c) */
