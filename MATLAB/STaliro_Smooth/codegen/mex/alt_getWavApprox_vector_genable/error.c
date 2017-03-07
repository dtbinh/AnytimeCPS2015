/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * error.c
 *
 * Code generation for function 'error'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "alt_getWavApprox_vector_genable.h"
#include "error.h"

/* Variable Definitions */
static emlrtRTEInfo t_emlrtRTEI = { 17, 9, "error",
  "/usr/local/MATLAB/R2015b/toolbox/eml/eml/+coder/+internal/error.m" };

/* Function Definitions */
void b_error(const emlrtStack *sp)
{
  emlrtErrorWithMessageIdR2012b(sp, &t_emlrtRTEI,
    "Coder:toolbox:reshape_emptyReshapeLimit", 0);
}

void error(const emlrtStack *sp)
{
  emlrtErrorWithMessageIdR2012b(sp, &t_emlrtRTEI,
    "Coder:toolbox:power_domainError", 0);
}

/* End of code generation (error.c) */
