/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * alt_getCoefficientsVector_genable_terminate.c
 *
 * Code generation for function 'alt_getCoefficientsVector_genable_terminate'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "alt_getCoefficientsVector_genable.h"
#include "alt_getCoefficientsVector_genable_terminate.h"
#include "_coder_alt_getCoefficientsVector_genable_mex.h"
#include "alt_getCoefficientsVector_genable_data.h"

/* Function Definitions */
void alt_getCoefficientsVector_genable_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

void alt_getCoefficientsVector_genable_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (alt_getCoefficientsVector_genable_terminate.c) */
