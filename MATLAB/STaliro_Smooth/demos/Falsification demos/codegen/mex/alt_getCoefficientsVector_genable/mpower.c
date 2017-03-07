/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mpower.c
 *
 * Code generation for function 'mpower'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "alt_getCoefficientsVector_genable.h"
#include "mpower.h"
#include "error.h"
#include "alt_getCoefficientsVector_genable_data.h"

/* Variable Definitions */
static emlrtRSInfo x_emlrtRSI = { 37, "mpower",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/ops/mpower.m" };

static emlrtRSInfo ab_emlrtRSI = { 61, "power",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/ops/power.m" };

/* Function Definitions */
real_T b_mpower(real_T a)
{
  return a * a;
}

real_T c_mpower(real_T a)
{
  return muDoubleScalarPower(a, 3.0);
}

real_T mpower(const emlrtStack *sp, real_T a, real_T b)
{
  real_T c;
  boolean_T p;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &x_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  b_st.site = &y_emlrtRSI;
  c = muDoubleScalarPower(a, b);
  p = false;
  if (a < 0.0) {
    if (muDoubleScalarIsNaN(b) || (muDoubleScalarFloor(b) == b)) {
      p = true;
    } else {
      p = false;
    }

    p = !p;
  }

  if (p) {
    c_st.site = &ab_emlrtRSI;
    error(&c_st);
  }

  return c;
}

/* End of code generation (mpower.c) */
