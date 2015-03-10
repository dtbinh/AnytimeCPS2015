/*
 * any.c
 *
 * Code generation for function 'any'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "any.h"
#include "eml_int_forloop_overflow_check.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRSInfo n_emlrtRSI = { 15, "any",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\any.m" };

static emlrtRSInfo o_emlrtRSI = { 124, "allOrAny",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\shared\\coder\\coder\\+coder\\+internal\\allOrAny.m"
};

/* Function Definitions */
void any(const emlrtStack *sp, const boolean_T x[5760000], boolean_T y[1920000])
{
  int32_T iy;
  int32_T i1;
  int32_T i2;
  int32_T j;
  boolean_T b_i1;
  int32_T ix;
  boolean_T exitg1;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &n_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  memset(&y[0], 0, 1920000U * sizeof(boolean_T));
  iy = -1;
  i1 = 0;
  i2 = 3840000;
  for (j = 0; j < 1920000; j++) {
    i1++;
    i2++;
    iy++;
    b_st.site = &o_emlrtRSI;
    if (i1 > i2) {
      b_i1 = false;
    } else {
      b_i1 = (i2 > 2145563647);
    }

    if (b_i1) {
      c_st.site = &p_emlrtRSI;
      check_forloop_overflow_error(&c_st);
    }

    ix = i1;
    exitg1 = false;
    while ((!exitg1) && (ix <= i2)) {
      if (!(x[ix - 1] == 0)) {
        y[iy] = true;
        exitg1 = true;
      } else {
        ix += 1920000;
      }
    }
  }
}

void b_any(const emlrtStack *sp, const boolean_T x[1920000], boolean_T y[1200])
{
  int32_T iy;
  int32_T i1;
  int32_T i2;
  int32_T j;
  boolean_T b_i1;
  int32_T ix;
  boolean_T exitg1;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &n_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  memset(&y[0], 0, 1200U * sizeof(boolean_T));
  iy = -1;
  i1 = 0;
  i2 = 1918800;
  for (j = 0; j < 1200; j++) {
    i1++;
    i2++;
    iy++;
    b_st.site = &o_emlrtRSI;
    if (i1 > i2) {
      b_i1 = false;
    } else {
      b_i1 = (i2 > 2147482447);
    }

    if (b_i1) {
      c_st.site = &p_emlrtRSI;
      check_forloop_overflow_error(&c_st);
    }

    ix = i1;
    exitg1 = false;
    while ((!exitg1) && (ix <= i2)) {
      if (!(x[ix - 1] == 0)) {
        y[iy] = true;
        exitg1 = true;
      } else {
        ix += 1200;
      }
    }
  }
}

boolean_T c_any(const boolean_T x[1200])
{
  boolean_T y;
  int32_T k;
  boolean_T exitg1;
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 1200)) {
    if (!(x[k] == 0)) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return y;
}

/* End of code generation (any.c) */
