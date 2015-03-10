/*
 * evalGaussianPrecomputedInv.c
 *
 * Code generation for function 'evalGaussianPrecomputedInv'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "evalGaussianPrecomputedInv.h"
#include "eml_error.h"
#include "eml_int_forloop_overflow_check.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRSInfo v_emlrtRSI = { 10, "evalGaussianPrecomputedInv",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\evalGaussianPrecomputedInv.m"
};

static emlrtRSInfo w_emlrtRSI = { 20, "det",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\matfun\\det.m"
};

static emlrtRSInfo x_emlrtRSI = { 8, "eml_xgetrf",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\eml_xgetrf.m"
};

static emlrtRSInfo y_emlrtRSI = { 8, "eml_lapack_xgetrf",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\internal\\eml_lapack_xgetrf.m"
};

static emlrtRSInfo ab_emlrtRSI = { 50, "eml_matlab_zgetrf",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zgetrf.m"
};

static emlrtRSInfo bb_emlrtRSI = { 58, "eml_matlab_zgetrf",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zgetrf.m"
};

static emlrtRSInfo cb_emlrtRSI = { 41, "eml_xgeru",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\blas\\eml_xgeru.m"
};

static emlrtRSInfo db_emlrtRSI = { 1, "xgeru",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\coder\\coder\\+coder\\+internal\\+blas\\xgeru.p"
};

static emlrtRSInfo eb_emlrtRSI = { 1, "xger",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\coder\\coder\\+coder\\+internal\\+blas\\xger.p"
};

static emlrtRSInfo fb_emlrtRSI = { 1, "xger",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\coder\\coder\\+coder\\+internal\\+refblas\\xger.p"
};

static emlrtRSInfo gb_emlrtRSI = { 1, "xgerx",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\coder\\coder\\+coder\\+internal\\+refblas\\xgerx.p"
};

/* Function Definitions */
void evalGaussianPrecomputedInv(c_run_perception_module_for_src *SD, const
  emlrtStack *sp, real_T data[5760000], const real_T mu[3], const real_T
  invsigma[9], real_T g[1920000])
{
  int32_T iy;
  int32_T jA;
  int32_T jy;
  int32_T j;
  real_T b_data[3];
  real_T smax;
  real_T y[3];
  real_T A[9];
  int8_T ipiv[3];
  int32_T c;
  int32_T ix;
  real_T s;
  int32_T b;
  boolean_T b_jA;
  int32_T ijA;
  boolean_T isodd;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack i_st;
  emlrtStack j_st;
  emlrtStack k_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  g_st.prev = &f_st;
  g_st.tls = f_st.tls;
  h_st.prev = &g_st;
  h_st.tls = g_st.tls;
  i_st.prev = &h_st;
  i_st.tls = h_st.tls;
  j_st.prev = &i_st;
  j_st.tls = i_st.tls;
  k_st.prev = &j_st;
  k_st.tls = j_st.tls;
  for (iy = 0; iy < 3; iy++) {
    jA = iy * 1920000;
    for (jy = 0; jy < 1920000; jy++) {
      SD->u1.f1.b[jA + jy] = mu[iy];
    }
  }

  for (iy = 0; iy < 5760000; iy++) {
    data[iy] -= SD->u1.f1.b[iy];
  }

  memset(&g[0], 0, 1920000U * sizeof(real_T));
  for (j = 0; j < 1920000; j++) {
    smax = 0.0;
    for (iy = 0; iy < 3; iy++) {
      b_data[iy] = 0.0;
      for (jA = 0; jA < 3; jA++) {
        b_data[iy] += data[j + 1920000 * jA] * invsigma[jA + 3 * iy];
      }

      y[iy] = -0.5 * b_data[iy];
      smax += y[iy] * data[j + 1920000 * iy];
    }

    g[j] = muDoubleScalarExp(smax);
    emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, sp);
  }

  st.site = &v_emlrtRSI;
  b_st.site = &w_emlrtRSI;
  c_st.site = &x_emlrtRSI;
  d_st.site = &y_emlrtRSI;
  memcpy(&A[0], &invsigma[0], 9U * sizeof(real_T));
  for (iy = 0; iy < 3; iy++) {
    ipiv[iy] = (int8_T)(1 + iy);
  }

  for (j = 0; j < 2; j++) {
    c = j << 2;
    iy = 0;
    ix = c;
    smax = muDoubleScalarAbs(A[c]);
    for (jA = 2; jA <= 3 - j; jA++) {
      ix++;
      s = muDoubleScalarAbs(A[ix]);
      if (s > smax) {
        iy = jA - 1;
        smax = s;
      }
    }

    if (A[c + iy] != 0.0) {
      if (iy != 0) {
        ipiv[j] = (int8_T)((j + iy) + 1);
        ix = j;
        iy += j;
        for (jA = 0; jA < 3; jA++) {
          smax = A[ix];
          A[ix] = A[iy];
          A[iy] = smax;
          ix += 3;
          iy += 3;
        }
      }

      b = (c - j) + 3;
      e_st.site = &ab_emlrtRSI;
      for (iy = c + 1; iy + 1 <= b; iy++) {
        A[iy] /= A[c];
      }
    }

    e_st.site = &bb_emlrtRSI;
    f_st.site = &cb_emlrtRSI;
    g_st.site = &db_emlrtRSI;
    h_st.site = &eb_emlrtRSI;
    i_st.site = &fb_emlrtRSI;
    jA = c;
    jy = c + 3;
    j_st.site = &gb_emlrtRSI;
    for (iy = 1; iy <= 2 - j; iy++) {
      smax = A[jy];
      if (A[jy] != 0.0) {
        ix = c + 1;
        b = (jA - j) + 6;
        j_st.site = &gb_emlrtRSI;
        if (jA + 5 > b) {
          b_jA = false;
        } else {
          b_jA = (b > 2147483646);
        }

        if (b_jA) {
          k_st.site = &p_emlrtRSI;
          check_forloop_overflow_error(&k_st);
        }

        for (ijA = jA + 4; ijA + 1 <= b; ijA++) {
          A[ijA] += A[ix] * -smax;
          ix++;
        }
      }

      jy += 3;
      jA += 3;
    }
  }

  smax = A[0];
  isodd = false;
  for (jA = 0; jA < 2; jA++) {
    smax *= A[(jA + 3 * (jA + 1)) + 1];
    if (ipiv[jA] > 1 + jA) {
      isodd = !isodd;
    }
  }

  if (isodd) {
    smax = -smax;
  }

  st.site = &v_emlrtRSI;
  if (smax < 0.0) {
    b_st.site = &hb_emlrtRSI;
    eml_error(&b_st);
  }

  smax = 0.063493635934240969 * muDoubleScalarSqrt(smax);
  for (iy = 0; iy < 1920000; iy++) {
    g[iy] *= smax;
  }
}

/* End of code generation (evalGaussianPrecomputedInv.c) */
