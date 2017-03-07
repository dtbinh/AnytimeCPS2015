/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * alt_getWavApprox_vector_genable_initialize.c
 *
 * Code generation for function 'alt_getWavApprox_vector_genable_initialize'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "alt_getWavApprox_vector_genable.h"
#include "alt_getWavApprox_vector_genable_initialize.h"
#include "_coder_alt_getWavApprox_vector_genable_mex.h"
#include "alt_getWavApprox_vector_genable_data.h"

/* Function Definitions */
void alt_getWavApprox_vector_genable_initialize(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (alt_getWavApprox_vector_genable_initialize.c) */
