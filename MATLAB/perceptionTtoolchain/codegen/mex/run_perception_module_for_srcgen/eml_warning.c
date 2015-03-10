/*
 * eml_warning.c
 *
 * Code generation for function 'eml_warning'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "eml_warning.h"
#include "eml_int_forloop_overflow_check.h"
#include "run_perception_module_for_srcgen_mexutil.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtMCInfo e_emlrtMCI = { 16, 13, "eml_warning",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_warning.m"
};

static emlrtMCInfo f_emlrtMCI = { 16, 5, "eml_warning",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_warning.m"
};

static emlrtRSInfo xe_emlrtRSI = { 16, "eml_warning",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_warning.m"
};

/* Function Declarations */
static void warning(const emlrtStack *sp, const mxArray *b, emlrtMCInfo
                    *location);

/* Function Definitions */
static void warning(const emlrtStack *sp, const mxArray *b, emlrtMCInfo
                    *location)
{
  const mxArray *pArray;
  pArray = b;
  emlrtCallMATLABR2012b(sp, 0, NULL, 1, &pArray, "warning", true, location);
}

void b_eml_warning(const emlrtStack *sp, const char_T varargin_2[14])
{
  const mxArray *y;
  static const int32_T iv5[2] = { 1, 33 };

  const mxArray *m6;
  char_T cv11[33];
  int32_T i;
  static const char_T cv12[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i', 'o',
    'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  const mxArray *b_y;
  static const int32_T iv6[2] = { 1, 14 };

  char_T b_varargin_2[14];
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  y = NULL;
  m6 = emlrtCreateCharArray(2, iv5);
  for (i = 0; i < 33; i++) {
    cv11[i] = cv12[i];
  }

  emlrtInitCharArrayR2013a(sp, 33, m6, cv11);
  emlrtAssign(&y, m6);
  b_y = NULL;
  m6 = emlrtCreateCharArray(2, iv6);
  for (i = 0; i < 14; i++) {
    b_varargin_2[i] = varargin_2[i];
  }

  emlrtInitCharArrayR2013a(sp, 14, m6, b_varargin_2);
  emlrtAssign(&b_y, m6);
  st.site = &xe_emlrtRSI;
  warning(&st, message(&st, y, b_y, &e_emlrtMCI), &f_emlrtMCI);
}

void c_eml_warning(const emlrtStack *sp)
{
  const mxArray *y;
  static const int32_T iv18[2] = { 1, 24 };

  const mxArray *m13;
  char_T cv33[24];
  int32_T i;
  static const char_T cv34[24] = { 'M', 'A', 'T', 'L', 'A', 'B', ':', 'e', 'i',
    'g', ':', 'N', 'o', 'C', 'o', 'n', 'v', 'e', 'r', 'g', 'e', 'n', 'c', 'e' };

  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  y = NULL;
  m13 = emlrtCreateCharArray(2, iv18);
  for (i = 0; i < 24; i++) {
    cv33[i] = cv34[i];
  }

  emlrtInitCharArrayR2013a(sp, 24, m13, cv33);
  emlrtAssign(&y, m13);
  st.site = &xe_emlrtRSI;
  warning(&st, b_message(&st, y, &e_emlrtMCI), &f_emlrtMCI);
}

void eml_warning(const emlrtStack *sp)
{
  const mxArray *y;
  static const int32_T iv4[2] = { 1, 27 };

  const mxArray *m5;
  char_T cv9[27];
  int32_T i;
  static const char_T cv10[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a', 't',
    'r', 'i', 'x' };

  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  y = NULL;
  m5 = emlrtCreateCharArray(2, iv4);
  for (i = 0; i < 27; i++) {
    cv9[i] = cv10[i];
  }

  emlrtInitCharArrayR2013a(sp, 27, m5, cv9);
  emlrtAssign(&y, m5);
  st.site = &xe_emlrtRSI;
  warning(&st, b_message(&st, y, &e_emlrtMCI), &f_emlrtMCI);
}

/* End of code generation (eml_warning.c) */
