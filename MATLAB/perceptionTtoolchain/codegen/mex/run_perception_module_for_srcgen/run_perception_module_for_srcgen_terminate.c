/*
 * run_perception_module_for_srcgen_terminate.c
 *
 * Code generation for function 'run_perception_module_for_srcgen_terminate'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "run_perception_module_for_srcgen_terminate.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */
void run_perception_module_for_srcgen_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

void run_perception_module_for_srcgen_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (run_perception_module_for_srcgen_terminate.c) */
