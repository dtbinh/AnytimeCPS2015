/*
 * validateattributes.c
 *
 * Code generation for function 'validateattributes'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "validateattributes.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtMCInfo j_emlrtMCI = { 171, 28, "validateattributes",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\lang\\validateattributes.m"
};

static emlrtMCInfo k_emlrtMCI = { 138, 28, "validateattributes",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\lang\\validateattributes.m"
};

static emlrtRSInfo if_emlrtRSI = { 138, "validateattributes",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\lang\\validateattributes.m"
};

static emlrtRSInfo jf_emlrtRSI = { 171, "validateattributes",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\lang\\validateattributes.m"
};

/* Function Declarations */
static void c_error(const emlrtStack *sp, const mxArray *b, const mxArray *c,
                    emlrtMCInfo *location);

/* Function Definitions */
static void c_error(const emlrtStack *sp, const mxArray *b, const mxArray *c,
                    emlrtMCInfo *location)
{
  const mxArray *pArrays[2];
  pArrays[0] = b;
  pArrays[1] = c;
  emlrtCallMATLABR2012b(sp, 0, NULL, 2, pArrays, "error", true, location);
}

void validateattributes(const emlrtStack *sp, const real_T a[2])
{
  boolean_T p;
  int32_T i;
  boolean_T exitg2;
  const mxArray *y;
  static const int32_T iv8[2] = { 1, 30 };

  const mxArray *m8;
  char_T cv15[30];
  static const char_T cv16[30] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'p', 'a',
    'd', 'a', 'r', 'r', 'a', 'y', ':', 'e', 'x', 'p', 'e', 'c', 't', 'e', 'd',
    'N', 'o', 'n', 'N', 'a', 'N' };

  const mxArray *b_y;
  static const int32_T iv9[2] = { 1, 48 };

  char_T cv17[48];
  static const char_T cv18[48] = { 'E', 'x', 'p', 'e', 'c', 't', 'e', 'd', ' ',
    'i', 'n', 'p', 'u', 't', ' ', 'n', 'u', 'm', 'b', 'e', 'r', ' ', '2', ',',
    ' ', 'P', 'A', 'D', 'S', 'I', 'Z', 'E', ',', ' ', 't', 'o', ' ', 'b', 'e',
    ' ', 'n', 'o', 'n', '-', 'N', 'a', 'N', '.' };

  boolean_T exitg1;
  boolean_T b_p;
  const mxArray *c_y;
  static const int32_T iv10[2] = { 1, 31 };

  char_T cv19[31];
  static const char_T cv20[31] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'p', 'a',
    'd', 'a', 'r', 'r', 'a', 'y', ':', 'e', 'x', 'p', 'e', 'c', 't', 'e', 'd',
    'I', 'n', 't', 'e', 'g', 'e', 'r' };

  const mxArray *d_y;
  static const int32_T iv11[2] = { 1, 55 };

  char_T cv21[55];
  static const char_T cv22[55] = { 'E', 'x', 'p', 'e', 'c', 't', 'e', 'd', ' ',
    'i', 'n', 'p', 'u', 't', ' ', 'n', 'u', 'm', 'b', 'e', 'r', ' ', '2', ',',
    ' ', 'P', 'A', 'D', 'S', 'I', 'Z', 'E', ',', ' ', 't', 'o', ' ', 'b', 'e',
    ' ', 'i', 'n', 't', 'e', 'g', 'e', 'r', '-', 'v', 'a', 'l', 'u', 'e', 'd',
    '.' };

  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  p = true;
  i = 0;
  exitg2 = false;
  while ((!exitg2) && (i < 2)) {
    if (!muDoubleScalarIsNaN(a[i])) {
      i++;
    } else {
      p = false;
      exitg2 = true;
    }
  }

  if (p) {
  } else {
    y = NULL;
    m8 = emlrtCreateCharArray(2, iv8);
    for (i = 0; i < 30; i++) {
      cv15[i] = cv16[i];
    }

    emlrtInitCharArrayR2013a(sp, 30, m8, cv15);
    emlrtAssign(&y, m8);
    b_y = NULL;
    m8 = emlrtCreateCharArray(2, iv9);
    for (i = 0; i < 48; i++) {
      cv17[i] = cv18[i];
    }

    emlrtInitCharArrayR2013a(sp, 48, m8, cv17);
    emlrtAssign(&b_y, m8);
    st.site = &jf_emlrtRSI;
    c_error(&st, y, b_y, &j_emlrtMCI);
  }

  p = true;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 2)) {
    if ((!muDoubleScalarIsInf(a[i])) && (!muDoubleScalarIsNaN(a[i])) &&
        (muDoubleScalarFloor(a[i]) == a[i])) {
      b_p = true;
    } else {
      b_p = false;
    }

    if (b_p) {
      i++;
    } else {
      p = false;
      exitg1 = true;
    }
  }

  if (p) {
  } else {
    c_y = NULL;
    m8 = emlrtCreateCharArray(2, iv10);
    for (i = 0; i < 31; i++) {
      cv19[i] = cv20[i];
    }

    emlrtInitCharArrayR2013a(sp, 31, m8, cv19);
    emlrtAssign(&c_y, m8);
    d_y = NULL;
    m8 = emlrtCreateCharArray(2, iv11);
    for (i = 0; i < 55; i++) {
      cv21[i] = cv22[i];
    }

    emlrtInitCharArrayR2013a(sp, 55, m8, cv21);
    emlrtAssign(&d_y, m8);
    st.site = &if_emlrtRSI;
    c_error(&st, c_y, d_y, &k_emlrtMCI);
  }
}

/* End of code generation (validateattributes.c) */
