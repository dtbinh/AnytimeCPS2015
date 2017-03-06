/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * log2.c
 *
 * Code generation for function 'log2'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "alt_getCoefficientsVector_genable.h"
#include "log2.h"

/* Function Definitions */
real_T b_log2(real_T x)
{
  real_T f;
  int32_T eint;
  real_T fdbl;
  fdbl = frexp(x, &eint);
  if (fdbl == 0.5) {
    f = (real_T)eint - 1.0;
  } else {
    f = muDoubleScalarLog(fdbl) / 0.69314718055994529 + (real_T)eint;
  }

  return f;
}

/* End of code generation (log2.c) */
