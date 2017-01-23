/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * alt_getCoefficientsVector_genable.c
 *
 * Code generation for function 'alt_getCoefficientsVector_genable'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "alt_getCoefficientsVector_genable.h"
#include "mpower.h"
#include "MeyerWavelet.h"
#include "alt_getCoefficientsVector_genable_emxutil.h"
#include "permn2.h"
#include "alt_getCoefficientsVector_genable_data.h"

/* Variable Definitions */
static emlrtRTEInfo emlrtRTEI = { 61, 17, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo emlrtRSI = { 9, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo b_emlrtRSI = { 11, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo c_emlrtRSI = { 12, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo d_emlrtRSI = { 20, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo e_emlrtRSI = { 25, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo f_emlrtRSI = { 43, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo g_emlrtRSI = { 48, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo h_emlrtRSI = { 61, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo i_emlrtRSI = { 63, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo j_emlrtRSI = { 66, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo k_emlrtRSI = { 71, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo l_emlrtRSI = { 72, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo m_emlrtRSI = { 80, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo n_emlrtRSI = { 21, "colon",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/ops/colon.m" };

static emlrtRSInfo o_emlrtRSI = { 79, "colon",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/ops/colon.m" };

static emlrtRSInfo p_emlrtRSI = { 283, "colon",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/ops/colon.m" };

static emlrtRSInfo q_emlrtRSI = { 291, "colon",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/ops/colon.m" };

static emlrtRSInfo bb_emlrtRSI = { 10, "MeyerWavelet",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/MeyerWavelet.m" };

static emlrtRSInfo cb_emlrtRSI = { 13, "MeyerWavelet",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/MeyerWavelet.m" };

static emlrtRSInfo db_emlrtRSI = { 16, "MeyerWavelet",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/MeyerWavelet.m" };

static emlrtRSInfo eb_emlrtRSI = { 37, "MeyerWavelet",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/MeyerWavelet.m" };

static emlrtRSInfo fb_emlrtRSI = { 43, "MeyerWavelet",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/MeyerWavelet.m" };

static emlrtRSInfo gb_emlrtRSI = { 49, "MeyerWavelet",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/MeyerWavelet.m" };

static emlrtRSInfo hb_emlrtRSI = { 55, "MeyerWavelet",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/MeyerWavelet.m" };

static emlrtRTEInfo b_emlrtRTEI = { 1, 26, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo c_emlrtRTEI = { 9, 1, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo f_emlrtRTEI = { 11, 1, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtBCInfo emlrtBCI = { -1, -1, 12, 6, "K",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo b_emlrtBCI = { -1, -1, 36, 36, "K",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtRTEInfo g_emlrtRTEI = { 55, 5, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtBCInfo c_emlrtBCI = { -1, -1, 63, 44, "K",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtRTEInfo h_emlrtRTEI = { 404, 15, "colon",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/ops/colon.m" };

static emlrtBCInfo d_emlrtBCI = { -1, -1, 82, 21, "D_ejk",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo e_emlrtBCI = { -1, -1, 82, 26, "D_ejk",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo f_emlrtBCI = { -1, -1, 50, 15, "C_00k",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

/* Function Declarations */
static int32_T asr_s32(int32_T u, uint32_T n);
static const mxArray *emlrt_marshallOut(const real_T u[4]);

/* Function Definitions */
static int32_T asr_s32(int32_T u, uint32_T n)
{
  int32_T y;
  if (u >= 0) {
    y = (int32_T)((uint32_T)u >> n);
  } else {
    y = -(int32_T)((uint32_T)-(u + 1) >> n) - 1;
  }

  return y;
}

static const mxArray *emlrt_marshallOut(const real_T u[4])
{
  const mxArray *y;
  static const int32_T iv4[2] = { 1, 4 };

  const mxArray *m2;
  real_T *pData;
  int32_T i;
  y = NULL;
  m2 = emlrtCreateNumericArray(2, iv4, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T *)mxGetPr(m2);
  for (i = 0; i < 4; i++) {
    pData[i] = u[i];
  }

  emlrtAssign(&y, m2);
  return y;
}

void alt_getCoefficientsVector_genable(const emlrtStack *sp, const real_T
  grid_x[81], const real_T dist_array_xy[6561], real_T dx, real_T j_min, real_T
  j_max, real_T k_min, real_T k_max, const real_T E_dash[8], real_T viz,
  emxArray_real_T *C_00k, emxArray_real_T *D_ejk)
{
  int32_T n;
  real_T anew;
  real_T apnd;
  boolean_T n_too_large;
  real_T ndbl;
  real_T cdiff;
  real_T absa;
  real_T absb;
  emxArray_real_T *r0;
  int32_T i0;
  int32_T nm1d2;
  int32_T k;
  emxArray_real_T *K;
  real_T d0;
  int32_T i;
  real_T dv0[2];
  int32_T k_sz;
  real_T X[13122];
  real_T b_grid_x[81];
  real_T phis[2];
  real_T psis[2];
  int32_T k_dims;
  real_T summation_C;
  int32_T x_dims;
  real_T x[2];
  int32_T dimen;
  int32_T e;
  real_T j_ix;
  int32_T j;
  real_T b_j;
  real_T summation_D;
  real_T dv1[4];
  boolean_T guard1 = false;
  real_T psi_1_den;
  real_T psi_1;
  real_T psi_2_den;
  real_T psi_2;
  real_T bigPsi_temp[2];
  real_T b_psis;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);

  /* see Nonlinear Approximation, R. A. DeVore, Acta Numerica 1998, Cambridge */
  /* University Press */
  /* % */
  st.site = &emlrtRSI;
  b_st.site = &n_emlrtRSI;
  c_st.site = &o_emlrtRSI;
  if (muDoubleScalarIsNaN(k_min) || muDoubleScalarIsNaN(k_max)) {
    n = 1;
    anew = rtNaN;
    apnd = k_max;
    n_too_large = false;
  } else if (k_max < k_min) {
    n = 0;
    anew = k_min;
    apnd = k_max;
    n_too_large = false;
  } else if (muDoubleScalarIsInf(k_min) || muDoubleScalarIsInf(k_max)) {
    n = 1;
    anew = rtNaN;
    apnd = k_max;
    n_too_large = !(k_min == k_max);
  } else {
    anew = k_min;
    ndbl = muDoubleScalarFloor((k_max - k_min) + 0.5);
    apnd = k_min + ndbl;
    cdiff = apnd - k_max;
    absa = muDoubleScalarAbs(k_min);
    absb = muDoubleScalarAbs(k_max);
    if (muDoubleScalarAbs(cdiff) < 4.4408920985006262E-16 * muDoubleScalarMax
        (absa, absb)) {
      ndbl++;
      apnd = k_max;
    } else if (cdiff > 0.0) {
      apnd = k_min + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    n_too_large = (2.147483647E+9 < ndbl);
    if (ndbl >= 0.0) {
      n = (int32_T)ndbl;
    } else {
      n = 0;
    }
  }

  d_st.site = &p_emlrtRSI;
  if (!n_too_large) {
  } else {
    emlrtErrorWithMessageIdR2012b(&d_st, &h_emlrtRTEI, "Coder:MATLAB:pmaxsize",
      0);
  }

  emxInit_real_T(&d_st, &r0, 2, &b_emlrtRTEI, true);
  i0 = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = n;
  emxEnsureCapacity(&c_st, (emxArray__common *)r0, i0, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  if (n > 0) {
    r0->data[0] = anew;
    if (n > 1) {
      r0->data[n - 1] = apnd;
      i0 = n - 1;
      nm1d2 = asr_s32(i0, 1U);
      d_st.site = &q_emlrtRSI;
      for (k = 1; k < nm1d2; k++) {
        r0->data[k] = anew + (real_T)k;
        r0->data[(n - k) - 1] = apnd - (real_T)k;
      }

      if (nm1d2 << 1 == n - 1) {
        r0->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        r0->data[nm1d2] = anew + (real_T)nm1d2;
        r0->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
      }
    }
  }

  emxInit_real_T(&c_st, &K, 2, &c_emlrtRTEI, true);
  i0 = K->size[0] * K->size[1];
  st.site = &emlrtRSI;
  K->size[0] = (int32_T)mpower(r0->size[1]);
  K->size[1] = 2;
  emxEnsureCapacity(sp, (emxArray__common *)K, i0, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  st.site = &emlrtRSI;
  d0 = mpower(r0->size[1]);
  nm1d2 = (int32_T)d0 << 1;
  for (i0 = 0; i0 < nm1d2; i0++) {
    K->data[i0] = 0.0;
  }

  st.site = &b_emlrtRSI;
  b_st.site = &n_emlrtRSI;
  c_st.site = &o_emlrtRSI;
  if (muDoubleScalarIsNaN(k_min) || muDoubleScalarIsNaN(k_max)) {
    n = 1;
    anew = rtNaN;
    apnd = k_max;
    n_too_large = false;
  } else if (k_max < k_min) {
    n = 0;
    anew = k_min;
    apnd = k_max;
    n_too_large = false;
  } else if (muDoubleScalarIsInf(k_min) || muDoubleScalarIsInf(k_max)) {
    n = 1;
    anew = rtNaN;
    apnd = k_max;
    n_too_large = !(k_min == k_max);
  } else {
    anew = k_min;
    ndbl = muDoubleScalarFloor((k_max - k_min) + 0.5);
    apnd = k_min + ndbl;
    cdiff = apnd - k_max;
    absa = muDoubleScalarAbs(k_min);
    absb = muDoubleScalarAbs(k_max);
    if (muDoubleScalarAbs(cdiff) < 4.4408920985006262E-16 * muDoubleScalarMax
        (absa, absb)) {
      ndbl++;
      apnd = k_max;
    } else if (cdiff > 0.0) {
      apnd = k_min + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    n_too_large = (2.147483647E+9 < ndbl);
    if (ndbl >= 0.0) {
      n = (int32_T)ndbl;
    } else {
      n = 0;
    }
  }

  d_st.site = &p_emlrtRSI;
  if (!n_too_large) {
  } else {
    emlrtErrorWithMessageIdR2012b(&d_st, &h_emlrtRTEI, "Coder:MATLAB:pmaxsize",
      0);
  }

  i0 = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = n;
  emxEnsureCapacity(&c_st, (emxArray__common *)r0, i0, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  if (n > 0) {
    r0->data[0] = anew;
    if (n > 1) {
      r0->data[n - 1] = apnd;
      i0 = n - 1;
      nm1d2 = asr_s32(i0, 1U);
      d_st.site = &q_emlrtRSI;
      for (k = 1; k < nm1d2; k++) {
        r0->data[k] = anew + (real_T)k;
        r0->data[(n - k) - 1] = apnd - (real_T)k;
      }

      if (nm1d2 << 1 == n - 1) {
        r0->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        r0->data[nm1d2] = anew + (real_T)nm1d2;
        r0->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
      }
    }
  }

  st.site = &b_emlrtRSI;
  d0 = mpower(r0->size[1]);
  emlrtForLoopVectorCheckR2012b(1.0, 1.0, d0, mxDOUBLE_CLASS, (int32_T)d0,
    &f_emlrtRTEI, sp);
  i = 0;
  while (i <= (int32_T)d0 - 1) {
    st.site = &c_emlrtRSI;
    b_st.site = &n_emlrtRSI;
    c_st.site = &o_emlrtRSI;
    if (muDoubleScalarIsNaN(k_min) || muDoubleScalarIsNaN(k_max)) {
      n = 1;
      anew = rtNaN;
      apnd = k_max;
      n_too_large = false;
    } else if (k_max < k_min) {
      n = 0;
      anew = k_min;
      apnd = k_max;
      n_too_large = false;
    } else if (muDoubleScalarIsInf(k_min) || muDoubleScalarIsInf(k_max)) {
      n = 1;
      anew = rtNaN;
      apnd = k_max;
      n_too_large = !(k_min == k_max);
    } else {
      anew = k_min;
      ndbl = muDoubleScalarFloor((k_max - k_min) + 0.5);
      apnd = k_min + ndbl;
      cdiff = apnd - k_max;
      absa = muDoubleScalarAbs(k_min);
      absb = muDoubleScalarAbs(k_max);
      if (muDoubleScalarAbs(cdiff) < 4.4408920985006262E-16 * muDoubleScalarMax
          (absa, absb)) {
        ndbl++;
        apnd = k_max;
      } else if (cdiff > 0.0) {
        apnd = k_min + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      n_too_large = (2.147483647E+9 < ndbl);
      if (ndbl >= 0.0) {
        n = (int32_T)ndbl;
      } else {
        n = 0;
      }
    }

    d_st.site = &p_emlrtRSI;
    if (!n_too_large) {
    } else {
      emlrtErrorWithMessageIdR2012b(&d_st, &h_emlrtRTEI, "Coder:MATLAB:pmaxsize",
        0);
    }

    i0 = r0->size[0] * r0->size[1];
    r0->size[0] = 1;
    r0->size[1] = n;
    emxEnsureCapacity(&c_st, (emxArray__common *)r0, i0, (int32_T)sizeof(real_T),
                      &b_emlrtRTEI);
    if (n > 0) {
      r0->data[0] = anew;
      if (n > 1) {
        r0->data[n - 1] = apnd;
        i0 = n - 1;
        nm1d2 = asr_s32(i0, 1U);
        d_st.site = &q_emlrtRSI;
        for (k = 1; k < nm1d2; k++) {
          r0->data[k] = anew + (real_T)k;
          r0->data[(n - k) - 1] = apnd - (real_T)k;
        }

        if (nm1d2 << 1 == n - 1) {
          r0->data[nm1d2] = (anew + apnd) / 2.0;
        } else {
          r0->data[nm1d2] = anew + (real_T)nm1d2;
          r0->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
        }
      }
    }

    st.site = &c_emlrtRSI;
    permn2(&st, r0, 1.0 + (real_T)i, dv0);
    nm1d2 = K->size[0];
    if (!((i + 1 >= 1) && (i + 1 <= nm1d2))) {
      emlrtDynamicBoundsCheckR2012b(i + 1, 1, nm1d2, &emlrtBCI, sp);
    }

    for (i0 = 0; i0 < 2; i0++) {
      K->data[i + K->size[0] * i0] = dv0[i0];
    }

    i++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  /* K = permn(k_min:k_max,dim); */
  k_sz = K->size[0];
  memset(&X[0], 0, 13122U * sizeof(real_T));
  i = 0;
  while (i < 6561) {
    memcpy(&b_grid_x[0], &grid_x[0], 81U * sizeof(real_T));
    st.site = &d_emlrtRSI;
    b_permn2(&st, b_grid_x, 1.0 + (real_T)i, dv0);
    for (i0 = 0; i0 < 2; i0++) {
      X[i + 6561 * i0] = dv0[i0];
    }

    i++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  /* X = permn(grid_x,dim); */
  st.site = &e_emlrtRSI;
  b_st.site = &n_emlrtRSI;
  c_st.site = &o_emlrtRSI;
  if (muDoubleScalarIsNaN(j_min) || muDoubleScalarIsNaN(j_max)) {
    n = 1;
    anew = rtNaN;
    apnd = j_max;
    n_too_large = false;
  } else if (j_max < j_min) {
    n = 0;
    anew = j_min;
    apnd = j_max;
    n_too_large = false;
  } else if (muDoubleScalarIsInf(j_min) || muDoubleScalarIsInf(j_max)) {
    n = 1;
    anew = rtNaN;
    apnd = j_max;
    n_too_large = !(j_min == j_max);
  } else {
    anew = j_min;
    ndbl = muDoubleScalarFloor((j_max - j_min) + 0.5);
    apnd = j_min + ndbl;
    cdiff = apnd - j_max;
    absa = muDoubleScalarAbs(j_min);
    absb = muDoubleScalarAbs(j_max);
    if (muDoubleScalarAbs(cdiff) < 4.4408920985006262E-16 * muDoubleScalarMax
        (absa, absb)) {
      ndbl++;
      apnd = j_max;
    } else if (cdiff > 0.0) {
      apnd = j_min + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    n_too_large = (2.147483647E+9 < ndbl);
    if (ndbl >= 0.0) {
      n = (int32_T)ndbl;
    } else {
      n = 0;
    }
  }

  d_st.site = &p_emlrtRSI;
  if (!n_too_large) {
  } else {
    emlrtErrorWithMessageIdR2012b(&d_st, &h_emlrtRTEI, "Coder:MATLAB:pmaxsize",
      0);
  }

  i0 = r0->size[0] * r0->size[1];
  r0->size[0] = 1;
  r0->size[1] = n;
  emxEnsureCapacity(&c_st, (emxArray__common *)r0, i0, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  if (n > 0) {
    r0->data[0] = anew;
    if (n > 1) {
      r0->data[n - 1] = apnd;
      i0 = n - 1;
      nm1d2 = asr_s32(i0, 1U);
      d_st.site = &q_emlrtRSI;
      for (k = 1; k < nm1d2; k++) {
        r0->data[k] = anew + (real_T)k;
        r0->data[(n - k) - 1] = apnd - (real_T)k;
      }

      if (nm1d2 << 1 == n - 1) {
        r0->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        r0->data[nm1d2] = anew + (real_T)nm1d2;
        r0->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
      }
    }
  }

  i0 = D_ejk->size[0] * D_ejk->size[1] * D_ejk->size[2];
  D_ejk->size[0] = 4;
  D_ejk->size[1] = r0->size[1];
  D_ejk->size[2] = K->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)D_ejk, i0, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  nm1d2 = (r0->size[1] << 2) * K->size[0];
  for (i0 = 0; i0 < nm1d2; i0++) {
    D_ejk->data[i0] = 0.0;
  }

  i0 = C_00k->size[0] * C_00k->size[1] * C_00k->size[2];
  C_00k->size[0] = 1;
  C_00k->size[1] = 1;
  C_00k->size[2] = K->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)C_00k, i0, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  nm1d2 = K->size[0];
  for (i0 = 0; i0 < nm1d2; i0++) {
    C_00k->data[i0] = 0.0;
  }

  for (i0 = 0; i0 < 2; i0++) {
    phis[i0] = 0.0;
    psis[i0] = 0.0;
  }

  /* % */
  /* compute C_00k */
  k_dims = 1;
  while (k_dims - 1 <= k_sz - 1) {
    summation_C = 0.0;
    x_dims = 0;
    while (x_dims < 6561) {
      i0 = K->size[0];
      if (!((k_dims >= 1) && (k_dims <= i0))) {
        emlrtDynamicBoundsCheckR2012b(k_dims, 1, i0, &b_emlrtBCI, sp);
      }

      for (i0 = 0; i0 < 2; i0++) {
        x[i0] = X[x_dims + 6561 * i0] - K->data[(k_dims + K->size[0] * i0) - 1];
      }

      /* [phis,~] = arrayfun(@(t) MeyerWavelet(t),x); */
      /* phis = (2^0)*phis'; */
      dimen = 0;
      while (dimen < 2) {
        st.site = &f_emlrtRSI;
        phis[dimen] = MeyerWavelet(x[dimen]);
        dimen++;
        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b(sp);
        }
      }

      st.site = &g_emlrtRSI;
      summation_C += mpower(dx) * dist_array_xy[x_dims] * (phis[0] * phis[1]);

      /* check use of dim and dx here */
      x_dims++;
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b(sp);
      }
    }

    i0 = C_00k->size[2];
    if (!((k_dims >= 1) && (k_dims <= i0))) {
      emlrtDynamicBoundsCheckR2012b(k_dims, 1, i0, &f_emlrtBCI, sp);
    }

    C_00k->data[C_00k->size[0] * C_00k->size[1] * (k_dims - 1)] = summation_C;
    k_dims++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  e = 0;
  while (e < 3) {
    j_ix = 0.0;
    i0 = (int32_T)(j_max + (1.0 - j_min));
    emlrtForLoopVectorCheckR2012b(j_min, 1.0, j_max, mxDOUBLE_CLASS, i0,
      &g_emlrtRTEI, sp);
    j = 0;
    while (j <= i0 - 1) {
      b_j = j_min + (real_T)j;
      j_ix++;
      k_dims = 0;
      while (k_dims <= k_sz - 1) {
        /* k along each dim */
        summation_D = 0.0;
        x_dims = 0;
        while (x_dims < 6561) {
          if (viz != 0.0) {
            st.site = &h_emlrtRSI;
            b_st.site = &n_emlrtRSI;
            c_st.site = &o_emlrtRSI;
            if (muDoubleScalarIsNaN(j_min) || muDoubleScalarIsNaN(j_max)) {
              n = 1;
              anew = rtNaN;
              apnd = j_max;
              n_too_large = false;
            } else if (j_max < j_min) {
              n = 0;
              anew = j_min;
              apnd = j_max;
              n_too_large = false;
            } else if (muDoubleScalarIsInf(j_min) || muDoubleScalarIsInf(j_max))
            {
              n = 1;
              anew = rtNaN;
              apnd = j_max;
              n_too_large = !(j_min == j_max);
            } else {
              anew = j_min;
              ndbl = muDoubleScalarFloor((j_max - j_min) + 0.5);
              apnd = j_min + ndbl;
              cdiff = apnd - j_max;
              absa = muDoubleScalarAbs(j_min);
              absb = muDoubleScalarAbs(j_max);
              if (muDoubleScalarAbs(cdiff) < 4.4408920985006262E-16 *
                  muDoubleScalarMax(absa, absb)) {
                ndbl++;
                apnd = j_max;
              } else if (cdiff > 0.0) {
                apnd = j_min + (ndbl - 1.0);
              } else {
                ndbl++;
              }

              n_too_large = (2.147483647E+9 < ndbl);
              if (ndbl >= 0.0) {
                n = (int32_T)ndbl;
              } else {
                n = 0;
              }
            }

            d_st.site = &p_emlrtRSI;
            if (!n_too_large) {
            } else {
              emlrtErrorWithMessageIdR2012b(&d_st, &h_emlrtRTEI,
                "Coder:MATLAB:pmaxsize", 0);
            }

            k = r0->size[0] * r0->size[1];
            r0->size[0] = 1;
            r0->size[1] = n;
            emxEnsureCapacity(&c_st, (emxArray__common *)r0, k, (int32_T)sizeof
                              (real_T), &b_emlrtRTEI);
            if (n > 0) {
              r0->data[0] = anew;
              if (n > 1) {
                r0->data[n - 1] = apnd;
                k = n - 1;
                nm1d2 = asr_s32(k, 1U);
                d_st.site = &q_emlrtRSI;
                for (k = 1; k < nm1d2; k++) {
                  r0->data[k] = anew + (real_T)k;
                  r0->data[(n - k) - 1] = apnd - (real_T)k;
                }

                if (nm1d2 << 1 == n - 1) {
                  r0->data[nm1d2] = (anew + apnd) / 2.0;
                } else {
                  r0->data[nm1d2] = anew + (real_T)nm1d2;
                  r0->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
                }
              }
            }

            dv1[0] = (1.0 + (real_T)e) / 3.0;
            dv1[1] = j_ix / (real_T)r0->size[1];
            dv1[2] = (1.0 + (real_T)k_dims) / (real_T)k_sz;
            dv1[3] = (1.0 + (real_T)x_dims) / 6561.0;
            emlrtDisplayR2012b(emlrt_marshallOut(dv1), "ans", &emlrtRTEI, sp);
          }

          st.site = &i_emlrtRSI;
          anew = c_mpower(b_j);
          k = K->size[0];
          if (!((k_dims + 1 >= 1) && (k_dims + 1 <= k))) {
            emlrtDynamicBoundsCheckR2012b(k_dims + 1, 1, k, &c_emlrtBCI, sp);
          }

          nm1d2 = k_dims + 1;
          for (k = 0; k < 2; k++) {
            x[k] = anew * X[x_dims + 6561 * k] - K->data[(nm1d2 + K->size[0] * k)
              - 1];
          }

          dimen = 0;
          while (dimen < 2) {
            st.site = &j_emlrtRSI;

            /* % Meyer wavelet (psi) and scale (phi) as in Valenzuela and Oliviera */
            guard1 = false;
            if (x[dimen] == 0.0) {
              guard1 = true;
            } else {
              b_st.site = &bb_emlrtRSI;
              if (x[dimen] == 0.75) {
                guard1 = true;
              } else {
                b_st.site = &bb_emlrtRSI;
                if (x[dimen] == -0.75) {
                  guard1 = true;
                } else {
                  b_st.site = &db_emlrtRSI;
                  anew = 50.26548245743669 * b_mpower(x[dimen]);
                  d0 = (muDoubleScalarSin(2.0943951023931953 * x[dimen]) + 4.0 *
                        x[dimen] / 3.0 * muDoubleScalarCos(12.566370614359172 *
                         x[dimen] / 3.0)) / (3.1415926535897931 * x[dimen] -
                    anew / 9.0);
                }
              }
            }

            if (guard1) {
              /* phi = 2/3 + 4/(3*pi); */
              b_st.site = &cb_emlrtRSI;
              anew = 3.1415926535897931 - 16.755160819145562 * mpower(x[dimen]);
              d0 = ((2.0943951023931953 * muDoubleScalarCos(2.0943951023931953 *
                      x[dimen]) + 1.3333333333333333 * muDoubleScalarCos
                     (4.1887902047863905 * x[dimen])) - 5.5850536063818534 *
                    x[dimen] * muDoubleScalarSin(4.1887902047863905 * x[dimen]))
                / anew;
            }

            /* evalue psi_1 */
            /* L'HopyBoy's rule at the points of 0/0 for psi_1 */
            if ((x[dimen] - 0.5 == 0.0) || (x[dimen] - 0.5 == 0.75) || (x[dimen]
                 - 0.5 == -0.75)) {
              b_st.site = &eb_emlrtRSI;
              psi_1_den = 1.0 - 5.333333333333333 * mpower(x[dimen] - 0.5);
              psi_1 = ((-0.88888888888888884 * (x[dimen] - 0.5) *
                        muDoubleScalarSin(2.0943951023931953 * (x[dimen] - 0.5))
                        + 0.42441318157838759 * muDoubleScalarCos
                        (2.0943951023931953 * (x[dimen] - 0.5))) -
                       1.3333333333333333 * muDoubleScalarCos(4.1887902047863905
                        * (x[dimen] - 0.5))) / psi_1_den;
            } else {
              b_st.site = &fb_emlrtRSI;
              psi_1_den = (x[dimen] - 0.5) - 1.7777777777777777 * b_mpower
                (x[dimen] - 0.5);
              psi_1 = (0.42441318157838759 * (x[dimen] - 0.5) *
                       muDoubleScalarCos(2.0943951023931953 * (x[dimen] - 0.5))
                       - 0.31830988618379069 * muDoubleScalarSin
                       (4.1887902047863905 * (x[dimen] - 0.5))) / psi_1_den;
            }

            /*  for psi_2 now */
            if ((x[dimen] - 0.5 == 0.0) || (x[dimen] - 0.5 == 0.375) || (x[dimen]
                 - 0.5 == -0.375)) {
              b_st.site = &gb_emlrtRSI;
              psi_2_den = 1.0 - 21.333333333333332 * mpower(x[dimen] - 0.5);
              psi_2 = ((-7.1111111111111107 * (x[dimen] - 0.5) *
                        muDoubleScalarSin(8.3775804095727811 * (x[dimen] - 0.5))
                        + 0.84882636315677518 * muDoubleScalarCos
                        (8.3775804095727811 * (x[dimen] - 0.5))) +
                       1.3333333333333333 * muDoubleScalarCos(4.1887902047863905
                        * (x[dimen] - 0.5))) / psi_2_den;
            } else {
              b_st.site = &hb_emlrtRSI;
              psi_2_den = (x[dimen] - 0.5) - 7.1111111111111107 * b_mpower
                (x[dimen] - 0.5);
              psi_2 = (0.84882636315677518 * (x[dimen] - 0.5) *
                       muDoubleScalarCos(8.3775804095727811 * (x[dimen] - 0.5))
                       + 0.31830988618379069 * muDoubleScalarSin
                       (4.1887902047863905 * (x[dimen] - 0.5))) / psi_2_den;
            }

            phis[dimen] = d0;
            psis[dimen] = psi_1 + psi_2;
            dimen++;
            if (*emlrtBreakCheckR2012bFlagVar != 0) {
              emlrtBreakCheckR2012b(sp);
            }
          }

          /* [phis,psis] = arrayfun(@(t) MeyerWavelet(t),x); */
          st.site = &k_emlrtRSI;
          anew = c_mpower(b_j);
          for (k = 0; k < 2; k++) {
            phis[k] *= anew;
          }

          st.site = &l_emlrtRSI;
          anew = c_mpower(b_j);

          /* keyboard */
          for (k = 0; k < 2; k++) {
            b_psis = anew * psis[k];
            bigPsi_temp[k] = (1.0 - E_dash[(e + (k << 2)) + 1]) * phis[k] +
              E_dash[(e + (k << 2)) + 1] * b_psis;
            psis[k] = b_psis;
          }

          /*  check if vectorization preserves locations in this % */
          st.site = &m_emlrtRSI;
          summation_D += mpower(dx) * dist_array_xy[x_dims] * (bigPsi_temp[0] *
            bigPsi_temp[1]);

          /* check use of dim and dx here */
          x_dims++;
          if (*emlrtBreakCheckR2012bFlagVar != 0) {
            emlrtBreakCheckR2012b(sp);
          }
        }

        k = D_ejk->size[1];
        nm1d2 = (int32_T)j_ix;
        if (!((nm1d2 >= 1) && (nm1d2 <= k))) {
          emlrtDynamicBoundsCheckR2012b(nm1d2, 1, k, &d_emlrtBCI, sp);
        }

        k = D_ejk->size[2];
        if (!((k_dims + 1 >= 1) && (k_dims + 1 <= k))) {
          emlrtDynamicBoundsCheckR2012b(k_dims + 1, 1, k, &e_emlrtBCI, sp);
        }

        D_ejk->data[(e + D_ejk->size[0] * (nm1d2 - 1)) + D_ejk->size[0] *
          D_ejk->size[1] * k_dims] = summation_D;
        k_dims++;
        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b(sp);
        }
      }

      j++;
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b(sp);
      }
    }

    e++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  emxFree_real_T(&r0);
  emxFree_real_T(&K);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (alt_getCoefficientsVector_genable.c) */
