/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * alt_getWavApprox_vector_genable.c
 *
 * Code generation for function 'alt_getWavApprox_vector_genable'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "alt_getWavApprox_vector_genable.h"
#include "log2.h"
#include "MeyerWavelet.h"
#include "alt_getWavApprox_vector_genable_emxutil.h"
#include "permn2.h"
#include "prod.h"
#include "mpower.h"
#include "alt_getWavApprox_vector_genable_mexutil.h"
#include "alt_getWavApprox_vector_genable_data.h"

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = { 5, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRSInfo b_emlrtRSI = { 7, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRSInfo c_emlrtRSI = { 9, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRSInfo d_emlrtRSI = { 10, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRSInfo e_emlrtRSI = { 24, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRSInfo f_emlrtRSI = { 27, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRSInfo g_emlrtRSI = { 37, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRSInfo h_emlrtRSI = { 41, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRSInfo i_emlrtRSI = { 50, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRTEInfo emlrtRTEI = { 1, 19, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRTEInfo b_emlrtRTEI = { 4, 1, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRTEInfo c_emlrtRTEI = { 7, 1, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRTEInfo d_emlrtRTEI = { 17, 1, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRTEInfo e_emlrtRTEI = { 18, 1, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRTEInfo f_emlrtRTEI = { 21, 5, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRTEInfo g_emlrtRTEI = { 46, 13, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRTEInfo h_emlrtRTEI = { 47, 13, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtECInfo emlrtECI = { 2, 49, 27, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtECInfo b_emlrtECI = { 2, 47, 21, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtBCInfo emlrtBCI = { -1, -1, 47, 23, "E",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtECInfo c_emlrtECI = { 2, 46, 21, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtBCInfo b_emlrtBCI = { -1, -1, 46, 26, "E",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtRTEInfo o_emlrtRTEI = { 40, 13, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtECInfo d_emlrtECI = { -1, 37, 21, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtBCInfo c_emlrtBCI = { -1, -1, 37, 33, "K",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtRTEInfo p_emlrtRTEI = { 34, 5, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtRTEInfo q_emlrtRTEI = { 23, 5, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtECInfo e_emlrtECI = { -1, 21, 13, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtBCInfo d_emlrtBCI = { -1, -1, 21, 25, "K",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtECInfo f_emlrtECI = { -1, 10, 4, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtBCInfo e_emlrtBCI = { -1, -1, 10, 6, "K",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtRTEInfo r_emlrtRTEI = { 9, 1, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m"
};

static emlrtDCInfo emlrtDCI = { 7, 36, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  1 };

static emlrtDCInfo b_emlrtDCI = { 7, 36, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  4 };

static emlrtDCInfo c_emlrtDCI = { 7, 11, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  1 };

static emlrtDCInfo d_emlrtDCI = { 7, 11, "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  4 };

static emlrtBCInfo f_emlrtBCI = { -1, -1, 4, 12, "E_dash",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtBCInfo g_emlrtBCI = { -1, -1, 51, 43, "D_ejk",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtBCInfo h_emlrtBCI = { -1, -1, 51, 45, "D_ejk",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtBCInfo i_emlrtBCI = { -1, -1, 51, 50, "D_ejk",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtBCInfo j_emlrtBCI = { -1, -1, 41, 58, "arg_x",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtBCInfo k_emlrtBCI = { -1, -1, 41, 18, "phis",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtBCInfo l_emlrtBCI = { -1, -1, 41, 30, "psis",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtBCInfo m_emlrtBCI = { -1, -1, 28, 39, "C_00k",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtBCInfo n_emlrtBCI = { -1, -1, 24, 40, "arg_x",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

static emlrtBCInfo o_emlrtBCI = { -1, -1, 24, 10, "phis",
  "alt_getWavApprox_vector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getWavApprox_vector_genable.m",
  0 };

/* Function Definitions */
real_T alt_getWavApprox_vector_genable(const emlrtStack *sp, const
  emxArray_real_T *x, const emxArray_real_T *C_00k, const emxArray_real_T *D_ejk,
  real_T k_min, real_T k_max, real_T j_min, real_T j_max, const emxArray_real_T *
  E_dash)
{
  real_T fhat_x;
  int32_T i0;
  int32_T i1;
  int32_T i2;
  emxArray_real_T *E;
  int32_T n;
  int32_T nm1d2;
  int32_T i3;
  real_T dim;
  real_T anew;
  real_T apnd;
  boolean_T n_too_large;
  real_T ndbl;
  real_T cdiff;
  real_T absa;
  real_T absb;
  emxArray_real_T *phis;
  int32_T k;
  emxArray_real_T *K;
  real_T d0;
  int32_T i;
  emxArray_real_T *psis;
  emxArray_int32_T *r0;
  int32_T iv0[2];
  int32_T k_sz;
  real_T summation;
  int32_T k_dims;
  emxArray_real_T *arg_x;
  int32_T dimen;
  real_T big_Phi;
  int32_T e;
  emxArray_real_T *phi_e;
  emxArray_real_T *psi_e;
  emxArray_real_T *r1;
  emxArray_real_T *b_phi_e;
  emxArray_real_T *b_E_dash;
  emxArray_real_T *c_E_dash;
  emxArray_real_T *d_E_dash;
  emxArray_real_T *e_E_dash;
  real_T j_ix;
  int32_T j;
  real_T b_j;
  int32_T i4;
  int32_T i5;
  int32_T f_E_dash[2];
  int32_T b_phis[2];
  int32_T g_E_dash[2];
  int32_T b_psis[2];
  int32_T c_phi_e[2];
  int32_T b_psi_e[2];
  real_T bigPsi_ejk_x;
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

  /* % */
  if (2 > E_dash->size[0]) {
    i0 = 0;
    i1 = 0;
  } else {
    i0 = 1;
    i2 = E_dash->size[0];
    i1 = E_dash->size[0];
    if (!((i1 >= 1) && (i1 <= i2))) {
      emlrtDynamicBoundsCheckR2012b(i1, 1, i2, &f_emlrtBCI, sp);
    }
  }

  emxInit_real_T(sp, &E, 2, &b_emlrtRTEI, true);
  n = E_dash->size[1];
  i2 = E->size[0] * E->size[1];
  E->size[0] = i1 - i0;
  E->size[1] = n;
  emxEnsureCapacity(sp, (emxArray__common *)E, i2, (int32_T)sizeof(real_T),
                    &emlrtRTEI);
  for (i2 = 0; i2 < n; i2++) {
    nm1d2 = i1 - i0;
    for (i3 = 0; i3 < nm1d2; i3++) {
      E->data[i3 + E->size[0] * i2] = E_dash->data[(i0 + i3) + E_dash->size[0] *
        i2];
    }
  }

  st.site = &emlrtRSI;
  dim = b_log2((real_T)(i1 - i0) + 1.0);
  st.site = &b_emlrtRSI;
  b_st.site = &j_emlrtRSI;
  c_st.site = &k_emlrtRSI;
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

  d_st.site = &l_emlrtRSI;
  if (!n_too_large) {
  } else {
    emlrtErrorWithMessageIdR2012b(&d_st, &n_emlrtRTEI, "Coder:MATLAB:pmaxsize",
      0);
  }

  emxInit_real_T(&d_st, &phis, 2, &d_emlrtRTEI, true);
  i2 = phis->size[0] * phis->size[1];
  phis->size[0] = 1;
  phis->size[1] = n;
  emxEnsureCapacity(&c_st, (emxArray__common *)phis, i2, (int32_T)sizeof(real_T),
                    &emlrtRTEI);
  if (n > 0) {
    phis->data[0] = anew;
    if (n > 1) {
      phis->data[n - 1] = apnd;
      i2 = n - 1;
      nm1d2 = asr_s32(i2, 1U);
      d_st.site = &m_emlrtRSI;
      for (k = 1; k < nm1d2; k++) {
        phis->data[k] = anew + (real_T)k;
        phis->data[(n - k) - 1] = apnd - (real_T)k;
      }

      if (nm1d2 << 1 == n - 1) {
        phis->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        phis->data[nm1d2] = anew + (real_T)nm1d2;
        phis->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
      }
    }
  }

  emxInit_real_T(&c_st, &K, 2, &c_emlrtRTEI, true);
  i2 = K->size[0] * K->size[1];
  st.site = &b_emlrtRSI;
  d0 = mpower(&st, phis->size[1], dim);
  if (!(d0 > 0.0)) {
    emlrtNonNegativeCheckR2012b(d0, &d_emlrtDCI, sp);
  }

  if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
    emlrtIntegerCheckR2012b(d0, &c_emlrtDCI, sp);
  }

  K->size[0] = (int32_T)d0;
  if (!(dim > 0.0)) {
    emlrtNonNegativeCheckR2012b(dim, &b_emlrtDCI, sp);
  }

  d0 = dim;
  if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
    emlrtIntegerCheckR2012b(d0, &emlrtDCI, sp);
  }

  K->size[1] = (int32_T)d0;
  emxEnsureCapacity(sp, (emxArray__common *)K, i2, (int32_T)sizeof(real_T),
                    &emlrtRTEI);
  st.site = &b_emlrtRSI;
  d0 = mpower(&st, phis->size[1], dim);
  if (!(d0 > 0.0)) {
    emlrtNonNegativeCheckR2012b(d0, &d_emlrtDCI, sp);
  }

  if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
    emlrtIntegerCheckR2012b(d0, &c_emlrtDCI, sp);
  }

  if (!(dim > 0.0)) {
    emlrtNonNegativeCheckR2012b(dim, &b_emlrtDCI, sp);
  }

  anew = dim;
  if (anew != (int32_T)muDoubleScalarFloor(anew)) {
    emlrtIntegerCheckR2012b(anew, &emlrtDCI, sp);
  }

  n = (int32_T)d0 * (int32_T)anew;
  for (i2 = 0; i2 < n; i2++) {
    K->data[i2] = 0.0;
  }

  st.site = &c_emlrtRSI;
  b_st.site = &j_emlrtRSI;
  c_st.site = &k_emlrtRSI;
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

  d_st.site = &l_emlrtRSI;
  if (!n_too_large) {
  } else {
    emlrtErrorWithMessageIdR2012b(&d_st, &n_emlrtRTEI, "Coder:MATLAB:pmaxsize",
      0);
  }

  i2 = phis->size[0] * phis->size[1];
  phis->size[0] = 1;
  phis->size[1] = n;
  emxEnsureCapacity(&c_st, (emxArray__common *)phis, i2, (int32_T)sizeof(real_T),
                    &emlrtRTEI);
  if (n > 0) {
    phis->data[0] = anew;
    if (n > 1) {
      phis->data[n - 1] = apnd;
      i2 = n - 1;
      nm1d2 = asr_s32(i2, 1U);
      d_st.site = &m_emlrtRSI;
      for (k = 1; k < nm1d2; k++) {
        phis->data[k] = anew + (real_T)k;
        phis->data[(n - k) - 1] = apnd - (real_T)k;
      }

      if (nm1d2 << 1 == n - 1) {
        phis->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        phis->data[nm1d2] = anew + (real_T)nm1d2;
        phis->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
      }
    }
  }

  st.site = &c_emlrtRSI;
  d0 = mpower(&st, phis->size[1], dim);
  emlrtForLoopVectorCheckR2012b(1.0, 1.0, d0, mxDOUBLE_CLASS, (int32_T)d0,
    &r_emlrtRTEI, sp);
  i = 0;
  emxInit_real_T(sp, &psis, 2, &e_emlrtRTEI, true);
  emxInit_int32_T(sp, &r0, 1, &emlrtRTEI, true);
  while (i <= (int32_T)d0 - 1) {
    i2 = K->size[0];
    i3 = i + 1;
    if (!((i3 >= 1) && (i3 <= i2))) {
      emlrtDynamicBoundsCheckR2012b(i3, 1, i2, &e_emlrtBCI, sp);
    }

    n = K->size[1];
    i2 = r0->size[0];
    r0->size[0] = n;
    emxEnsureCapacity(sp, (emxArray__common *)r0, i2, (int32_T)sizeof(int32_T),
                      &emlrtRTEI);
    for (i2 = 0; i2 < n; i2++) {
      r0->data[i2] = i2;
    }

    st.site = &d_emlrtRSI;
    b_st.site = &j_emlrtRSI;
    c_st.site = &k_emlrtRSI;
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

    d_st.site = &l_emlrtRSI;
    if (!n_too_large) {
    } else {
      emlrtErrorWithMessageIdR2012b(&d_st, &n_emlrtRTEI, "Coder:MATLAB:pmaxsize",
        0);
    }

    i2 = phis->size[0] * phis->size[1];
    phis->size[0] = 1;
    phis->size[1] = n;
    emxEnsureCapacity(&c_st, (emxArray__common *)phis, i2, (int32_T)sizeof
                      (real_T), &emlrtRTEI);
    if (n > 0) {
      phis->data[0] = anew;
      if (n > 1) {
        phis->data[n - 1] = apnd;
        i2 = n - 1;
        nm1d2 = asr_s32(i2, 1U);
        d_st.site = &m_emlrtRSI;
        for (k = 1; k < nm1d2; k++) {
          phis->data[k] = anew + (real_T)k;
          phis->data[(n - k) - 1] = apnd - (real_T)k;
        }

        if (nm1d2 << 1 == n - 1) {
          phis->data[nm1d2] = (anew + apnd) / 2.0;
        } else {
          phis->data[nm1d2] = anew + (real_T)nm1d2;
          phis->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
        }
      }
    }

    st.site = &d_emlrtRSI;
    permn2(&st, phis, dim, 1.0 + (real_T)i, psis);
    iv0[0] = 1;
    iv0[1] = r0->size[0];
    emlrtSubAssignSizeCheckR2012b(iv0, 2, *(int32_T (*)[2])psis->size, 2,
      &f_emlrtECI, sp);
    n = psis->size[1];
    for (i2 = 0; i2 < n; i2++) {
      K->data[i + K->size[0] * r0->data[i2]] = psis->data[psis->size[0] * i2];
    }

    i++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  emxFree_int32_T(&r0);

  /* K = permn(k_min:k_max,dim); */
  k_sz = K->size[0] - 1;
  summation = 0.0;
  i2 = phis->size[0] * phis->size[1];
  phis->size[0] = 1;
  phis->size[1] = (int32_T)dim;
  emxEnsureCapacity(sp, (emxArray__common *)phis, i2, (int32_T)sizeof(real_T),
                    &emlrtRTEI);
  n = (int32_T)dim;
  for (i2 = 0; i2 < n; i2++) {
    phis->data[i2] = 0.0;
  }

  i2 = psis->size[0] * psis->size[1];
  psis->size[0] = 1;
  psis->size[1] = (int32_T)dim;
  emxEnsureCapacity(sp, (emxArray__common *)psis, i2, (int32_T)sizeof(real_T),
                    &emlrtRTEI);
  n = (int32_T)dim;
  for (i2 = 0; i2 < n; i2++) {
    psis->data[i2] = 0.0;
  }

  /* % */
  k_dims = 1;
  emxInit_real_T1(sp, &arg_x, 1, &f_emlrtRTEI, true);
  while (k_dims - 1 <= k_sz) {
    n = K->size[1];
    i2 = K->size[0];
    if (!((k_dims >= 1) && (k_dims <= i2))) {
      emlrtDynamicBoundsCheckR2012b(k_dims, 1, i2, &d_emlrtBCI, sp);
    }

    i2 = arg_x->size[0];
    arg_x->size[0] = n;
    emxEnsureCapacity(sp, (emxArray__common *)arg_x, i2, (int32_T)sizeof(real_T),
                      &emlrtRTEI);
    for (i2 = 0; i2 < n; i2++) {
      arg_x->data[i2] = K->data[(k_dims + K->size[0] * i2) - 1];
    }

    i2 = x->size[0];
    i3 = arg_x->size[0];
    if (i2 != i3) {
      emlrtSizeEqCheck1DR2012b(i2, i3, &e_emlrtECI, sp);
    }

    i2 = arg_x->size[0];
    arg_x->size[0] = x->size[0];
    emxEnsureCapacity(sp, (emxArray__common *)arg_x, i2, (int32_T)sizeof(real_T),
                      &emlrtRTEI);
    n = x->size[0];
    for (i2 = 0; i2 < n; i2++) {
      arg_x->data[i2] = x->data[i2] - arg_x->data[i2];
    }

    emlrtForLoopVectorCheckR2012b(1.0, 1.0, dim, mxDOUBLE_CLASS, (int32_T)dim,
      &q_emlrtRTEI, sp);
    dimen = 1;
    while (dimen - 1 <= (int32_T)dim - 1) {
      i2 = arg_x->size[0];
      if (!((dimen >= 1) && (dimen <= i2))) {
        emlrtDynamicBoundsCheckR2012b(dimen, 1, i2, &n_emlrtBCI, sp);
      }

      i2 = phis->size[1];
      if (!((dimen >= 1) && (dimen <= i2))) {
        emlrtDynamicBoundsCheckR2012b(dimen, 1, i2, &o_emlrtBCI, sp);
      }

      st.site = &e_emlrtRSI;
      MeyerWavelet(arg_x->data[dimen - 1], &phis->data[dimen - 1], &anew);
      dimen++;
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b(sp);
      }
    }

    /* [phis,~] = arrayfun(@(t) MeyerWavelet(t),arg_x); %for all elements in vector x */
    st.site = &f_emlrtRSI;
    big_Phi = prod(&st, phis);
    i2 = C_00k->size[2];
    if (!((k_dims >= 1) && (k_dims <= i2))) {
      emlrtDynamicBoundsCheckR2012b(k_dims, 1, i2, &m_emlrtBCI, sp);
    }

    summation += C_00k->data[C_00k->size[0] * C_00k->size[1] * (k_dims - 1)] *
      big_Phi;
    k_dims++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  /* % */
  i2 = (i1 - i0) - 1;
  e = 0;
  emxInit_real_T(sp, &phi_e, 2, &g_emlrtRTEI, true);
  emxInit_real_T(sp, &psi_e, 2, &h_emlrtRTEI, true);
  emxInit_real_T1(sp, &r1, 1, &emlrtRTEI, true);
  emxInit_real_T(sp, &b_phi_e, 2, &emlrtRTEI, true);
  emxInit_real_T(sp, &b_E_dash, 2, &emlrtRTEI, true);
  emxInit_real_T(sp, &c_E_dash, 2, &emlrtRTEI, true);
  emxInit_real_T(sp, &d_E_dash, 2, &emlrtRTEI, true);
  emxInit_real_T(sp, &e_E_dash, 2, &emlrtRTEI, true);
  while (e <= i2) {
    j_ix = 0.0;
    i3 = (int32_T)(j_max + (1.0 - j_min));
    emlrtForLoopVectorCheckR2012b(j_min, 1.0, j_max, mxDOUBLE_CLASS, i3,
      &p_emlrtRTEI, sp);
    j = 0;
    while (j <= i3 - 1) {
      b_j = j_min + (real_T)j;
      j_ix++;
      k_dims = 1;
      while (k_dims - 1 <= k_sz) {
        st.site = &g_emlrtRSI;
        anew = mpower(&st, 2.0, b_j);
        i4 = arg_x->size[0];
        arg_x->size[0] = x->size[0];
        emxEnsureCapacity(sp, (emxArray__common *)arg_x, i4, (int32_T)sizeof
                          (real_T), &emlrtRTEI);
        n = x->size[0];
        for (i4 = 0; i4 < n; i4++) {
          arg_x->data[i4] = anew * x->data[i4];
        }

        n = K->size[1];
        i4 = K->size[0];
        if (!((k_dims >= 1) && (k_dims <= i4))) {
          emlrtDynamicBoundsCheckR2012b(k_dims, 1, i4, &c_emlrtBCI, sp);
        }

        i4 = r1->size[0];
        r1->size[0] = n;
        emxEnsureCapacity(sp, (emxArray__common *)r1, i4, (int32_T)sizeof(real_T),
                          &emlrtRTEI);
        for (i4 = 0; i4 < n; i4++) {
          r1->data[i4] = K->data[(k_dims + K->size[0] * i4) - 1];
        }

        i4 = arg_x->size[0];
        i5 = r1->size[0];
        if (i4 != i5) {
          emlrtSizeEqCheck1DR2012b(i4, i5, &d_emlrtECI, sp);
        }

        i4 = arg_x->size[0];
        emxEnsureCapacity(sp, (emxArray__common *)arg_x, i4, (int32_T)sizeof
                          (real_T), &emlrtRTEI);
        n = arg_x->size[0];
        for (i4 = 0; i4 < n; i4++) {
          arg_x->data[i4] -= r1->data[i4];
        }

        emlrtForLoopVectorCheckR2012b(1.0, 1.0, dim, mxDOUBLE_CLASS, (int32_T)
          dim, &o_emlrtRTEI, sp);
        dimen = 1;
        while (dimen - 1 <= (int32_T)dim - 1) {
          i4 = arg_x->size[0];
          if (!((dimen >= 1) && (dimen <= i4))) {
            emlrtDynamicBoundsCheckR2012b(dimen, 1, i4, &j_emlrtBCI, sp);
          }

          i4 = phis->size[1];
          if (!((dimen >= 1) && (dimen <= i4))) {
            emlrtDynamicBoundsCheckR2012b(dimen, 1, i4, &k_emlrtBCI, sp);
          }

          i4 = psis->size[1];
          if (!((dimen >= 1) && (dimen <= i4))) {
            emlrtDynamicBoundsCheckR2012b(dimen, 1, i4, &l_emlrtBCI, sp);
          }

          st.site = &h_emlrtRSI;
          MeyerWavelet(arg_x->data[dimen - 1], &phis->data[dimen - 1],
                       &psis->data[dimen - 1]);
          dimen++;
          if (*emlrtBreakCheckR2012bFlagVar != 0) {
            emlrtBreakCheckR2012b(sp);
          }
        }

        /* [phis,psis] = arrayfun(@(t) MeyerWavelet(t),arg_x); %for all elements in vector x */
        i4 = i1 - i0;
        i5 = e + 1;
        if (!((i5 >= 1) && (i5 <= i4))) {
          emlrtDynamicBoundsCheckR2012b(i5, 1, i4, &b_emlrtBCI, sp);
        }

        n = E_dash->size[1];
        nm1d2 = E_dash->size[1];
        i4 = b_E_dash->size[0] * b_E_dash->size[1];
        b_E_dash->size[0] = i1 - i0;
        b_E_dash->size[1] = nm1d2;
        emxEnsureCapacity(sp, (emxArray__common *)b_E_dash, i4, (int32_T)sizeof
                          (real_T), &emlrtRTEI);
        for (i4 = 0; i4 < nm1d2; i4++) {
          k = i1 - i0;
          for (i5 = 0; i5 < k; i5++) {
            b_E_dash->data[i5 + b_E_dash->size[0] * i4] = E_dash->data[(i0 + i5)
              + E_dash->size[0] * i4];
          }
        }

        i4 = c_E_dash->size[0] * c_E_dash->size[1];
        c_E_dash->size[0] = 1;
        c_E_dash->size[1] = n;
        emxEnsureCapacity(sp, (emxArray__common *)c_E_dash, i4, (int32_T)sizeof
                          (real_T), &emlrtRTEI);
        for (i4 = 0; i4 < n; i4++) {
          c_E_dash->data[c_E_dash->size[0] * i4] = b_E_dash->data[e +
            b_E_dash->size[0] * i4];
        }

        for (i4 = 0; i4 < 2; i4++) {
          f_E_dash[i4] = c_E_dash->size[i4];
        }

        for (i4 = 0; i4 < 2; i4++) {
          b_phis[i4] = phis->size[i4];
        }

        if ((f_E_dash[0] != b_phis[0]) || (f_E_dash[1] != b_phis[1])) {
          emlrtSizeEqCheckNDR2012b(&f_E_dash[0], &b_phis[0], &c_emlrtECI, sp);
        }

        n = E_dash->size[1];
        i4 = phi_e->size[0] * phi_e->size[1];
        phi_e->size[0] = 1;
        phi_e->size[1] = n;
        emxEnsureCapacity(sp, (emxArray__common *)phi_e, i4, (int32_T)sizeof
                          (real_T), &emlrtRTEI);
        for (i4 = 0; i4 < n; i4++) {
          phi_e->data[phi_e->size[0] * i4] = (1.0 - E->data[e + E->size[0] * i4])
            * phis->data[phis->size[0] * i4];
        }

        i4 = i1 - i0;
        i5 = e + 1;
        if (!((i5 >= 1) && (i5 <= i4))) {
          emlrtDynamicBoundsCheckR2012b(i5, 1, i4, &emlrtBCI, sp);
        }

        n = E_dash->size[1];
        nm1d2 = E_dash->size[1];
        i4 = d_E_dash->size[0] * d_E_dash->size[1];
        d_E_dash->size[0] = i1 - i0;
        d_E_dash->size[1] = nm1d2;
        emxEnsureCapacity(sp, (emxArray__common *)d_E_dash, i4, (int32_T)sizeof
                          (real_T), &emlrtRTEI);
        for (i4 = 0; i4 < nm1d2; i4++) {
          k = i1 - i0;
          for (i5 = 0; i5 < k; i5++) {
            d_E_dash->data[i5 + d_E_dash->size[0] * i4] = E_dash->data[(i0 + i5)
              + E_dash->size[0] * i4];
          }
        }

        i4 = e_E_dash->size[0] * e_E_dash->size[1];
        e_E_dash->size[0] = 1;
        e_E_dash->size[1] = n;
        emxEnsureCapacity(sp, (emxArray__common *)e_E_dash, i4, (int32_T)sizeof
                          (real_T), &emlrtRTEI);
        for (i4 = 0; i4 < n; i4++) {
          e_E_dash->data[e_E_dash->size[0] * i4] = d_E_dash->data[e +
            d_E_dash->size[0] * i4];
        }

        for (i4 = 0; i4 < 2; i4++) {
          g_E_dash[i4] = e_E_dash->size[i4];
        }

        for (i4 = 0; i4 < 2; i4++) {
          b_psis[i4] = psis->size[i4];
        }

        if ((g_E_dash[0] != b_psis[0]) || (g_E_dash[1] != b_psis[1])) {
          emlrtSizeEqCheckNDR2012b(&g_E_dash[0], &b_psis[0], &b_emlrtECI, sp);
        }

        n = E_dash->size[1];
        i4 = psi_e->size[0] * psi_e->size[1];
        psi_e->size[0] = 1;
        psi_e->size[1] = n;
        emxEnsureCapacity(sp, (emxArray__common *)psi_e, i4, (int32_T)sizeof
                          (real_T), &emlrtRTEI);
        for (i4 = 0; i4 < n; i4++) {
          psi_e->data[psi_e->size[0] * i4] = E->data[e + E->size[0] * i4] *
            psis->data[psis->size[0] * i4];
        }

        for (i4 = 0; i4 < 2; i4++) {
          c_phi_e[i4] = phi_e->size[i4];
        }

        for (i4 = 0; i4 < 2; i4++) {
          b_psi_e[i4] = psi_e->size[i4];
        }

        if ((c_phi_e[0] != b_psi_e[0]) || (c_phi_e[1] != b_psi_e[1])) {
          emlrtSizeEqCheckNDR2012b(&c_phi_e[0], &b_psi_e[0], &emlrtECI, sp);
        }

        i4 = b_phi_e->size[0] * b_phi_e->size[1];
        b_phi_e->size[0] = 1;
        b_phi_e->size[1] = phi_e->size[1];
        emxEnsureCapacity(sp, (emxArray__common *)b_phi_e, i4, (int32_T)sizeof
                          (real_T), &emlrtRTEI);
        n = phi_e->size[0] * phi_e->size[1];
        for (i4 = 0; i4 < n; i4++) {
          b_phi_e->data[i4] = phi_e->data[i4] + psi_e->data[i4];
        }

        st.site = &i_emlrtRSI;
        bigPsi_ejk_x = prod(&st, b_phi_e);
        i4 = D_ejk->size[0];
        i5 = 1 + e;
        if (!((i5 >= 1) && (i5 <= i4))) {
          emlrtDynamicBoundsCheckR2012b(i5, 1, i4, &g_emlrtBCI, sp);
        }

        i4 = D_ejk->size[1];
        nm1d2 = (int32_T)j_ix;
        if (!((nm1d2 >= 1) && (nm1d2 <= i4))) {
          emlrtDynamicBoundsCheckR2012b(nm1d2, 1, i4, &h_emlrtBCI, sp);
        }

        i4 = D_ejk->size[2];
        if (!((k_dims >= 1) && (k_dims <= i4))) {
          emlrtDynamicBoundsCheckR2012b(k_dims, 1, i4, &i_emlrtBCI, sp);
        }

        summation += D_ejk->data[((i5 + D_ejk->size[0] * (nm1d2 - 1)) +
          D_ejk->size[0] * D_ejk->size[1] * (k_dims - 1)) - 1] * bigPsi_ejk_x;
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

  emxFree_real_T(&e_E_dash);
  emxFree_real_T(&d_E_dash);
  emxFree_real_T(&c_E_dash);
  emxFree_real_T(&b_E_dash);
  emxFree_real_T(&b_phi_e);
  emxFree_real_T(&r1);
  emxFree_real_T(&psi_e);
  emxFree_real_T(&phi_e);
  emxFree_real_T(&arg_x);
  emxFree_real_T(&psis);
  emxFree_real_T(&phis);
  emxFree_real_T(&K);
  emxFree_real_T(&E);
  fhat_x = summation;
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
  return fhat_x;
}

/* End of code generation (alt_getWavApprox_vector_genable.c) */
