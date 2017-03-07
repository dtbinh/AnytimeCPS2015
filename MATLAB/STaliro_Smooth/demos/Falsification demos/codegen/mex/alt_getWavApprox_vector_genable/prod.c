/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * prod.c
 *
 * Code generation for function 'prod'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "alt_getWavApprox_vector_genable.h"
#include "prod.h"
#include "eml_int_forloop_overflow_check.h"
#include "alt_getWavApprox_vector_genable_data.h"

/* Variable Definitions */
static emlrtRSInfo pb_emlrtRSI = { 11, "prod",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/datafun/prod.m" };

static emlrtRSInfo qb_emlrtRSI = { 46, "sumprod",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/datafun/private/sumprod.m" };

static emlrtRSInfo rb_emlrtRSI = { 36, "combine_vector_elements",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/datafun/private/combine_vector_elements.m"
};

static emlrtRTEInfo w_emlrtRTEI = { 19, 15, "sumprod",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/datafun/private/sumprod.m" };

static emlrtRTEInfo x_emlrtRTEI = { 39, 9, "sumprod",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/datafun/private/sumprod.m" };

/* Function Definitions */
real_T prod(const emlrtStack *sp, const emxArray_real_T *x)
{
  real_T y;
  boolean_T overflow;
  boolean_T p;
  int32_T k;
  int32_T exitg1;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &pb_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  if ((x->size[1] == 1) || (x->size[1] != 1)) {
    overflow = true;
  } else {
    overflow = false;
  }

  if (overflow) {
  } else {
    emlrtErrorWithMessageIdR2012b(&st, &w_emlrtRTEI,
      "Coder:toolbox:autoDimIncompatibility", 0);
  }

  overflow = false;
  p = false;
  k = 0;
  do {
    exitg1 = 0;
    if (k < 2) {
      if (x->size[k] != 0) {
        exitg1 = 1;
      } else {
        k++;
      }
    } else {
      p = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  if (!p) {
  } else {
    overflow = true;
  }

  if (!overflow) {
  } else {
    emlrtErrorWithMessageIdR2012b(&st, &x_emlrtRTEI,
      "Coder:toolbox:UnsupportedSpecialEmpty", 0);
  }

  b_st.site = &qb_emlrtRSI;
  if (x->size[1] == 0) {
    y = 1.0;
  } else {
    y = x->data[0];
    c_st.site = &rb_emlrtRSI;
    if (2 > x->size[1]) {
      overflow = false;
    } else {
      overflow = (x->size[1] > 2147483646);
    }

    if (overflow) {
      d_st.site = &n_emlrtRSI;
      check_forloop_overflow_error(&d_st);
    }

    for (k = 2; k <= x->size[1]; k++) {
      y *= x->data[k - 1];
    }
  }

  return y;
}

/* End of code generation (prod.c) */
