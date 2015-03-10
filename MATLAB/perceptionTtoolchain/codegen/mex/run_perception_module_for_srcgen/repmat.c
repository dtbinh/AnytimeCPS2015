/*
 * repmat.c
 *
 * Code generation for function 'repmat'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "repmat.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "eml_warning.h"
#include "run_perception_module_for_srcgen_mexutil.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRSInfo rc_emlrtRSI = { 12, "repmat",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m"
};

static emlrtMCInfo p_emlrtMCI = { 51, 13, "eml_assert_valid_size_arg",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_assert_valid_size_arg.m"
};

static emlrtMCInfo q_emlrtMCI = { 50, 23, "eml_assert_valid_size_arg",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_assert_valid_size_arg.m"
};

static emlrtMCInfo r_emlrtMCI = { 57, 5, "eml_assert_valid_size_arg",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_assert_valid_size_arg.m"
};

static emlrtMCInfo s_emlrtMCI = { 56, 15, "eml_assert_valid_size_arg",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_assert_valid_size_arg.m"
};

static emlrtRTEInfo ab_emlrtRTEI = { 30, 1, "repmat",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m"
};

static emlrtRSInfo oe_emlrtRSI = { 56, "eml_assert_valid_size_arg",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_assert_valid_size_arg.m"
};

static emlrtRSInfo pe_emlrtRSI = { 50, "eml_assert_valid_size_arg",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_assert_valid_size_arg.m"
};

static emlrtRSInfo af_emlrtRSI = { 57, "eml_assert_valid_size_arg",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_assert_valid_size_arg.m"
};

static emlrtRSInfo hf_emlrtRSI = { 51, "eml_assert_valid_size_arg",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_assert_valid_size_arg.m"
};

/* Function Declarations */
static const mxArray *c_message(const emlrtStack *sp, const mxArray *b, const
  mxArray *c, const mxArray *d, emlrtMCInfo *location);
static void eml_assert_valid_size_arg(const emlrtStack *sp, real_T varargin_1);

/* Function Definitions */
static const mxArray *c_message(const emlrtStack *sp, const mxArray *b, const
  mxArray *c, const mxArray *d, emlrtMCInfo *location)
{
  const mxArray *pArrays[3];
  const mxArray *m19;
  pArrays[0] = b;
  pArrays[1] = c;
  pArrays[2] = d;
  return emlrtCallMATLABR2012b(sp, 1, &m19, 3, pArrays, "message", true,
    location);
}

static void eml_assert_valid_size_arg(const emlrtStack *sp, real_T varargin_1)
{
  boolean_T p;
  boolean_T guard1 = false;
  boolean_T b0;
  const mxArray *y;
  static const int32_T iv16[2] = { 1, 28 };

  const mxArray *m12;
  char_T cv29[28];
  int32_T i;
  static const char_T cv30[28] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 'N', 'o', 'n', 'I', 'n', 't', 'e', 'g', 'e', 'r', 'I',
    'n', 'p', 'u', 't' };

  const mxArray *b_y;
  const mxArray *c_y;
  real_T b_varargin_1;
  const mxArray *d_y;
  static const int32_T iv17[2] = { 1, 21 };

  char_T cv31[21];
  static const char_T cv32[21] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 'p', 'm', 'a', 'x', 's', 'i', 'z', 'e' };

  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = sp;
  b_st.tls = sp->tls;
  if ((varargin_1 != varargin_1) || muDoubleScalarIsInf(varargin_1)) {
    p = false;
  } else {
    p = true;
  }

  guard1 = false;
  if (p) {
    if (-2.147483648E+9 > varargin_1) {
      b0 = false;
    } else {
      b0 = true;
    }

    if (b0) {
      p = true;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    p = false;
  }

  if (p) {
  } else {
    y = NULL;
    m12 = emlrtCreateCharArray(2, iv16);
    for (i = 0; i < 28; i++) {
      cv29[i] = cv30[i];
    }

    emlrtInitCharArrayR2013a(sp, 28, m12, cv29);
    emlrtAssign(&y, m12);
    b_y = NULL;
    m12 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)mxGetData(m12) = MIN_int32_T;
    emlrtAssign(&b_y, m12);
    c_y = NULL;
    m12 = emlrtCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *(int32_T *)mxGetData(m12) = MAX_int32_T;
    emlrtAssign(&c_y, m12);
    st.site = &pe_emlrtRSI;
    b_st.site = &hf_emlrtRSI;
    b_error(&st, c_message(&b_st, y, b_y, c_y, &p_emlrtMCI), &q_emlrtMCI);
  }

  if (varargin_1 <= 0.0) {
    b_varargin_1 = 0.0;
  } else {
    b_varargin_1 = varargin_1;
  }

  if (2.147483647E+9 >= b_varargin_1) {
  } else {
    d_y = NULL;
    m12 = emlrtCreateCharArray(2, iv17);
    for (i = 0; i < 21; i++) {
      cv31[i] = cv32[i];
    }

    emlrtInitCharArrayR2013a(sp, 21, m12, cv31);
    emlrtAssign(&d_y, m12);
    st.site = &oe_emlrtRSI;
    b_st.site = &af_emlrtRSI;
    b_error(&st, b_message(&b_st, d_y, &r_emlrtMCI), &s_emlrtMCI);
  }
}

void b_repmat(const real_T a[1920000], real_T b[5760000])
{
  int32_T jtilecol;
  int32_T ibtile;
  int32_T jcol;
  int32_T iacol;
  int32_T ibmat;
  for (jtilecol = 0; jtilecol < 3; jtilecol++) {
    ibtile = jtilecol * 1920000;
    for (jcol = 0; jcol < 1600; jcol++) {
      iacol = jcol * 1200;
      ibmat = ibtile + jcol * 1200;
      memcpy(&b[ibmat], &a[iacol], 1200U * sizeof(real_T));
    }
  }
}

void c_repmat(const real_T a[4], real_T b[7680000])
{
  int32_T jcol;
  int32_T ibmat;
  int32_T itilerow;
  for (jcol = 0; jcol < 4; jcol++) {
    ibmat = jcol * 1920000;
    for (itilerow = 0; itilerow < 1920000; itilerow++) {
      b[ibmat + itilerow] = a[jcol];
    }
  }
}

void d_repmat(const real_T a[1920000], real_T b[7680000])
{
  int32_T jtilecol;
  int32_T ibtile;
  for (jtilecol = 0; jtilecol < 4; jtilecol++) {
    ibtile = jtilecol * 1920000;
    memcpy(&b[ibtile], &a[0], 1920000U * sizeof(real_T));
  }
}

void e_repmat(const emlrtStack *sp, const real_T a[2], real_T varargin_1,
              emxArray_real_T *b)
{
  int32_T i;
  int32_T ibmat;
  int32_T itilerow;
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &rc_emlrtRSI;
  eml_assert_valid_size_arg(&st, varargin_1);
  i = b->size[0] * b->size[1];
  b->size[0] = (int32_T)varargin_1;
  b->size[1] = 2;
  emxEnsureCapacity(sp, (emxArray__common *)b, i, (int32_T)sizeof(real_T),
                    &ab_emlrtRTEI);
  if ((int32_T)varargin_1 == 0) {
  } else {
    for (i = 0; i < 2; i++) {
      ibmat = i * (int32_T)varargin_1;
      for (itilerow = 1; itilerow <= (int32_T)varargin_1; itilerow++) {
        b->data[(ibmat + itilerow) - 1] = a[i];
      }
    }
  }
}

void repmat(const boolean_T a[1920000], boolean_T b[5760000])
{
  int32_T jtilecol;
  int32_T ibtile;
  int32_T jcol;
  int32_T iacol;
  int32_T ibmat;
  for (jtilecol = 0; jtilecol < 3; jtilecol++) {
    ibtile = jtilecol * 1920000;
    for (jcol = 0; jcol < 1600; jcol++) {
      iacol = jcol * 1200;
      ibmat = ibtile + jcol * 1200;
      memcpy(&b[ibmat], &a[iacol], 1200U * sizeof(boolean_T));
    }
  }
}

/* End of code generation (repmat.c) */
