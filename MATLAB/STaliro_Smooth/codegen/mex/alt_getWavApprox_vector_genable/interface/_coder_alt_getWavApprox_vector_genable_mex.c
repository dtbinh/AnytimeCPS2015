/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_alt_getWavApprox_vector_genable_mex.c
 *
 * Code generation for function '_coder_alt_getWavApprox_vector_genable_mex'
 *
 */

/* Include files */
#include "alt_getWavApprox_vector_genable.h"
#include "_coder_alt_getWavApprox_vector_genable_mex.h"
#include "alt_getWavApprox_vector_genable_terminate.h"
#include "_coder_alt_getWavApprox_vector_genable_api.h"
#include "alt_getWavApprox_vector_genable_initialize.h"
#include "alt_getWavApprox_vector_genable_data.h"

/* Variable Definitions */
static jmp_buf emlrtJBEnviron;

/* Function Declarations */
static void c_alt_getWavApprox_vector_genab(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[8]);

/* Function Definitions */
static void c_alt_getWavApprox_vector_genab(int32_T nlhs, mxArray *plhs[1],
  int32_T nrhs, const mxArray *prhs[8])
{
  int32_T n;
  const mxArray *inputs[8];
  const mxArray *outputs[1];
  int32_T b_nlhs;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 8) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 8, 4,
                        31, "alt_getWavApprox_vector_genable");
  }

  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 31,
                        "alt_getWavApprox_vector_genable");
  }

  /* Temporary copy for mex inputs. */
  for (n = 0; n < nrhs; n++) {
    inputs[n] = prhs[n];
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(&st);
    }
  }

  /* Call the function. */
  alt_getWavApprox_vector_genable_api(inputs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  alt_getWavApprox_vector_genable_terminate();
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  emlrtStack st = { NULL, NULL, NULL };

  mexAtExit(alt_getWavApprox_vector_genable_atexit);

  /* Initialize the memory manager. */
  omp_init_lock(&emlrtLockGlobal);
  omp_init_nest_lock(&emlrtNestLockGlobal);
  emlrtLoadLibrary("/usr/local/MATLAB/R2015b/sys/os/glnxa64/libiomp5.so");

  /* Module initialization. */
  alt_getWavApprox_vector_genable_initialize();
  st.tls = emlrtRootTLSGlobal;
  emlrtSetJmpBuf(&st, &emlrtJBEnviron);
  if (setjmp(emlrtJBEnviron) == 0) {
    /* Dispatch the entry-point. */
    c_alt_getWavApprox_vector_genab(nlhs, plhs, nrhs, prhs);
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&emlrtNestLockGlobal);
  } else {
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&emlrtNestLockGlobal);
    emlrtReportParallelRunTimeError(&st);
  }
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal,
                     emlrtLockerFunction, omp_get_num_procs());
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_alt_getWavApprox_vector_genable_mex.c) */
