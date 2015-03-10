/*
 * _coder_run_perception_module_for_srcgen_mex.c
 *
 * Code generation for function 'run_perception_module_for_srcgen'
 *
 */

/* Include files */
#include "mex.h"
#include "_coder_run_perception_module_for_srcgen_api.h"

/* Function Declarations */
static void run_perception_module_for_srcgen_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

/* Variable Definitions */
emlrtContext emlrtContextGlobal = { true, false, EMLRT_VERSION_INFO, NULL, "run_perception_module_for_srcgen", NULL, false, {2045744189U,2170104910U,2743257031U,4284093946U}, NULL };
void *emlrtRootTLSGlobal = NULL;

/* Function Definitions */
static void run_perception_module_for_srcgen_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  const mxArray *inputs[16];
  int n = 0;
  int nInputs = nrhs;
  emlrtStack st = { NULL, NULL, NULL };
  /* Module initialization. */
  run_perception_module_for_srcgen_initialize(&emlrtContextGlobal);
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 16) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, mxINT32_CLASS, 16, mxCHAR_CLASS, 32, "run_perception_module_for_srcgen");
  } else if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, mxCHAR_CLASS, 32, "run_perception_module_for_srcgen");
  }
  /* Temporary copy for mex inputs. */
  for (n = 0; n < nInputs; ++n) {
    inputs[n] = prhs[n];
  }
  /* Call the function. */
  run_perception_module_for_srcgen_api(inputs);
  /* Module finalization. */
  run_perception_module_for_srcgen_terminate();
}

void run_perception_module_for_srcgen_atexit_wrapper(void)
{
   run_perception_module_for_srcgen_atexit();
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /* Initialize the memory manager. */
  mexAtExit(run_perception_module_for_srcgen_atexit_wrapper);
  /* Dispatch the entry-point. */
  run_perception_module_for_srcgen_mexFunction(nlhs, plhs, nrhs, prhs);
}
/* End of code generation (_coder_run_perception_module_for_srcgen_mex.c) */
