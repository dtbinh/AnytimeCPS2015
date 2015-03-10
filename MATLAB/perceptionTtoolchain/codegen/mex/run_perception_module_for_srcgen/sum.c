/*
 * sum.c
 *
 * Code generation for function 'sum'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "sum.h"
#include "eml_warning.h"
#include "run_perception_module_for_srcgen_mexutil.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRSInfo he_emlrtRSI = { 13, "sum",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\datafun\\sum.m"
};

static emlrtRSInfo ie_emlrtRSI = { 19, "sumprod",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumprod.m"
};

static emlrtRSInfo je_emlrtRSI = { 38, "sumprod",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumprod.m"
};

/* Function Definitions */
void b_sum(const real_T x[7680000], real_T y[1920000])
{
  int32_T iy;
  int32_T ixstart;
  int32_T j;
  int32_T ix;
  real_T s;
  int32_T k;
  iy = -1;
  ixstart = -1;
  for (j = 0; j < 1920000; j++) {
    ixstart++;
    ix = ixstart;
    s = x[ixstart];
    for (k = 0; k < 3; k++) {
      ix += 1920000;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

void c_sum(const emlrtStack *sp, const emxArray_real_T *x, real_T y[2])
{
  boolean_T cond;
  const mxArray *b_y;
  static const int32_T iv19[2] = { 1, 36 };

  const mxArray *m14;
  char_T cv35[36];
  int32_T i;
  static const char_T cv36[36] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o',
    'l', 'b', 'o', 'x', ':', 'a', 'u', 't', 'o', 'D', 'i', 'm', 'I', 'n', 'c',
    'o', 'm', 'p', 'a', 't', 'i', 'b', 'i', 'l', 'i', 't', 'y' };

  boolean_T p;
  int32_T ixstart;
  int32_T exitg1;
  const mxArray *c_y;
  static const int32_T iv20[2] = { 1, 37 };

  char_T cv37[37];
  static const char_T cv38[37] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o',
    'l', 'b', 'o', 'x', ':', 'U', 'n', 's', 'u', 'p', 'p', 'o', 'r', 't', 'e',
    'd', 'S', 'p', 'e', 'c', 'i', 'a', 'l', 'E', 'm', 'p', 't', 'y' };

  int32_T ix;
  int32_T iy;
  real_T s;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &he_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  cond = (x->size[0] != 1);
  b_st.site = &ie_emlrtRSI;
  if (cond) {
  } else {
    b_y = NULL;
    m14 = emlrtCreateCharArray(2, iv19);
    for (i = 0; i < 36; i++) {
      cv35[i] = cv36[i];
    }

    emlrtInitCharArrayR2013a(&b_st, 36, m14, cv35);
    emlrtAssign(&b_y, m14);
    c_st.site = &ne_emlrtRSI;
    b_error(&c_st, b_message(&c_st, b_y, &i_emlrtMCI), &i_emlrtMCI);
  }

  cond = false;
  p = false;
  ixstart = 0;
  do {
    exitg1 = 0;
    if (ixstart < 2) {
      if (x->size[ixstart] != 0) {
        exitg1 = 1;
      } else {
        ixstart++;
      }
    } else {
      p = true;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  if (!p) {
  } else {
    cond = true;
  }

  b_st.site = &je_emlrtRSI;
  if (!cond) {
  } else {
    c_y = NULL;
    m14 = emlrtCreateCharArray(2, iv20);
    for (i = 0; i < 37; i++) {
      cv37[i] = cv38[i];
    }

    emlrtInitCharArrayR2013a(&b_st, 37, m14, cv37);
    emlrtAssign(&c_y, m14);
    c_st.site = &ne_emlrtRSI;
    b_error(&c_st, b_message(&c_st, c_y, &i_emlrtMCI), &i_emlrtMCI);
  }

  if (x->size[0] == 0) {
    for (ixstart = 0; ixstart < 2; ixstart++) {
      y[ixstart] = 0.0;
    }
  } else {
    ix = -1;
    iy = -1;
    for (i = 0; i < 2; i++) {
      ixstart = ix + 1;
      ix++;
      s = x->data[ixstart];
      for (ixstart = 2; ixstart <= x->size[0]; ixstart++) {
        ix++;
        s += x->data[ix];
      }

      iy++;
      y[iy] = s;
    }
  }
}

void sum(const real_T x[5760000], real_T y[1920000])
{
  int32_T iy;
  int32_T ixstart;
  int32_T j;
  int32_T ix;
  real_T s;
  int32_T k;
  iy = -1;
  ixstart = -1;
  for (j = 0; j < 1920000; j++) {
    ixstart++;
    ix = ixstart;
    s = x[ixstart];
    for (k = 0; k < 2; k++) {
      ix += 1920000;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

/* End of code generation (sum.c) */
