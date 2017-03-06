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
#include "log2.h"
#include "MeyerWavelet.h"
#include "alt_getCoefficientsVector_genable_emxutil.h"
#include "permn2.h"
#include "mpower.h"
#include "prod.h"
#include "alt_getCoefficientsVector_genable_mexutil.h"
#include "alt_getCoefficientsVector_genable_data.h"

/* Variable Definitions */
static emlrtRTEInfo emlrtRTEI = { 61, 17, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo emlrtRSI = { 7, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo b_emlrtRSI = { 9, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo c_emlrtRSI = { 11, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo d_emlrtRSI = { 12, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo e_emlrtRSI = { 17, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo f_emlrtRSI = { 19, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo g_emlrtRSI = { 20, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo h_emlrtRSI = { 25, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo i_emlrtRSI = { 43, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo j_emlrtRSI = { 46, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo k_emlrtRSI = { 48, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo l_emlrtRSI = { 61, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo m_emlrtRSI = { 63, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo n_emlrtRSI = { 66, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo o_emlrtRSI = { 71, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo p_emlrtRSI = { 72, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo q_emlrtRSI = { 77, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRSInfo r_emlrtRSI = { 80, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo b_emlrtRTEI = { 1, 26, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo c_emlrtRTEI = { 6, 1, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo d_emlrtRTEI = { 9, 1, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo e_emlrtRTEI = { 17, 1, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo f_emlrtRTEI = { 29, 1, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo g_emlrtRTEI = { 30, 1, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo h_emlrtRTEI = { 36, 9, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo i_emlrtRTEI = { 74, 17, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo j_emlrtRTEI = { 75, 17, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtBCInfo emlrtBCI = { -1, -1, 6, 12, "E_dash",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtDCInfo emlrtDCI = { 9, 11, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  4 };

static emlrtDCInfo b_emlrtDCI = { 9, 11, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  1 };

static emlrtDCInfo c_emlrtDCI = { 9, 36, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  4 };

static emlrtDCInfo d_emlrtDCI = { 9, 36, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  1 };

static emlrtRTEInfo p_emlrtRTEI = { 11, 1, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtBCInfo b_emlrtBCI = { -1, -1, 12, 6, "K",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtECInfo emlrtECI = { -1, 12, 4, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo q_emlrtRTEI = { 19, 1, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtBCInfo c_emlrtBCI = { -1, -1, 20, 6, "X",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtECInfo b_emlrtECI = { -1, 20, 4, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtBCInfo d_emlrtBCI = { -1, -1, 36, 21, "X",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo e_emlrtBCI = { -1, -1, 36, 36, "K",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtECInfo c_emlrtECI = { -1, 36, 13,
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo r_emlrtRTEI = { 42, 9, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtBCInfo f_emlrtBCI = { -1, -1, 47, 15, "dist_array_xy",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtRTEInfo s_emlrtRTEI = { 55, 5, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtBCInfo g_emlrtBCI = { -1, -1, 63, 29, "X",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo h_emlrtBCI = { -1, -1, 63, 44, "K",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtECInfo d_emlrtECI = { -1, 63, 21,
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtRTEInfo t_emlrtRTEI = { 65, 17, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtBCInfo i_emlrtBCI = { -1, -1, 74, 30, "E",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtECInfo e_emlrtECI = { 2, 74, 25, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtBCInfo j_emlrtBCI = { -1, -1, 75, 27, "E",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtECInfo f_emlrtECI = { 2, 75, 25, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtECInfo g_emlrtECI = { 2, 76, 31, "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m"
};

static emlrtBCInfo k_emlrtBCI = { -1, -1, 79, 23, "dist_array_xy",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo l_emlrtBCI = { -1, -1, 82, 19, "D_ejk",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo m_emlrtBCI = { -1, -1, 82, 21, "D_ejk",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo n_emlrtBCI = { -1, -1, 82, 26, "D_ejk",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo o_emlrtBCI = { -1, -1, 66, 61, "x",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo p_emlrtBCI = { -1, -1, 66, 21, "phis",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo q_emlrtBCI = { -1, -1, 66, 33, "psis",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo r_emlrtBCI = { -1, -1, 50, 15, "C_00k",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo s_emlrtBCI = { -1, -1, 43, 45, "x",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

static emlrtBCInfo t_emlrtBCI = { -1, -1, 43, 12, "phis",
  "alt_getCoefficientsVector_genable",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/alt_getCoefficientsVector_genable.m",
  0 };

/* Function Declarations */
static const mxArray *emlrt_marshallOut(const real_T u[4]);

/* Function Definitions */
static const mxArray *emlrt_marshallOut(const real_T u[4])
{
  const mxArray *y;
  static const int32_T iv4[2] = { 1, 4 };

  const mxArray *m1;
  real_T *pData;
  int32_T i;
  y = NULL;
  m1 = emlrtCreateNumericArray(2, iv4, mxDOUBLE_CLASS, mxREAL);
  pData = (real_T *)mxGetPr(m1);
  for (i = 0; i < 4; i++) {
    pData[i] = u[i];
  }

  emlrtAssign(&y, m1);
  return y;
}

void alt_getCoefficientsVector_genable(const emlrtStack *sp, const
  emxArray_real_T *grid_x, const emxArray_real_T *dist_array_xy, real_T dx,
  real_T j_min, real_T j_max, real_T k_min, real_T k_max, const emxArray_real_T *
  E_dash, real_T viz, emxArray_real_T *C_00k, emxArray_real_T *D_ejk)
{
  int32_T i0;
  int32_T i1;
  int32_T i2;
  emxArray_real_T *E;
  int32_T loop_ub;
  int32_T nm1d2;
  int32_T i3;
  real_T dim;
  int32_T n;
  real_T anew;
  real_T apnd;
  boolean_T n_too_large;
  real_T ndbl;
  real_T cdiff;
  real_T absa;
  real_T absb;
  emxArray_real_T *psi_e;
  int32_T k;
  emxArray_real_T *K;
  real_T d0;
  int32_T i;
  emxArray_real_T *phi_e;
  emxArray_int32_T *r0;
  int32_T iv0[2];
  emxArray_real_T *X;
  int32_T k_sz;
  emxArray_real_T *b_grid_x;
  int32_T iv1[2];
  int32_T x_sz;
  emxArray_real_T *phis;
  emxArray_real_T *psis;
  int32_T k_dims;
  emxArray_real_T *x;
  emxArray_real_T *r1;
  real_T summation_C;
  int32_T x_dims;
  int32_T dimen;
  real_T bigPhi_00k_x;
  int32_T e;
  emxArray_real_T *b_phi_e;
  emxArray_real_T *b_E_dash;
  emxArray_real_T *c_E_dash;
  emxArray_real_T *d_E_dash;
  emxArray_real_T *e_E_dash;
  real_T j_ix;
  int32_T j;
  real_T b_j;
  real_T summation_D;
  int32_T i4;
  real_T dv0[4];
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

  /* see Nonlinear Approximation, R. A. DeVore, Acta Numerica 1998, Cambridge */
  /* University Press */
  /* % */
  if (2 > E_dash->size[0]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = 2;
    i1 = E_dash->size[0];
    i2 = E_dash->size[0];
    if (!((i2 >= 1) && (i2 <= i1))) {
      emlrtDynamicBoundsCheckR2012b(i2, 1, i1, &emlrtBCI, sp);
    }

    i1 = i2 + 1;
  }

  emxInit_real_T(sp, &E, 2, &c_emlrtRTEI, true);
  loop_ub = E_dash->size[1];
  i2 = E->size[0] * E->size[1];
  E->size[0] = i1 - i0;
  E->size[1] = loop_ub;
  emxEnsureCapacity(sp, (emxArray__common *)E, i2, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  for (i2 = 0; i2 < loop_ub; i2++) {
    nm1d2 = i1 - i0;
    for (i3 = 0; i3 < nm1d2; i3++) {
      E->data[i3 + E->size[0] * i2] = E_dash->data[((i0 + i3) + E_dash->size[0] *
        i2) - 1];
    }
  }

  st.site = &emlrtRSI;
  dim = b_log2((real_T)(i1 - i0) + 1.0);
  st.site = &b_emlrtRSI;
  b_st.site = &s_emlrtRSI;
  c_st.site = &t_emlrtRSI;
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

  d_st.site = &u_emlrtRSI;
  if (!n_too_large) {
  } else {
    emlrtErrorWithMessageIdR2012b(&d_st, &u_emlrtRTEI, "Coder:MATLAB:pmaxsize",
      0);
  }

  emxInit_real_T(&d_st, &psi_e, 2, &j_emlrtRTEI, true);
  i2 = psi_e->size[0] * psi_e->size[1];
  psi_e->size[0] = 1;
  psi_e->size[1] = n;
  emxEnsureCapacity(&c_st, (emxArray__common *)psi_e, i2, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  if (n > 0) {
    psi_e->data[0] = anew;
    if (n > 1) {
      psi_e->data[n - 1] = apnd;
      i2 = n - 1;
      nm1d2 = asr_s32(i2, 1U);
      d_st.site = &v_emlrtRSI;
      for (k = 1; k < nm1d2; k++) {
        psi_e->data[k] = anew + (real_T)k;
        psi_e->data[(n - k) - 1] = apnd - (real_T)k;
      }

      if (nm1d2 << 1 == n - 1) {
        psi_e->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        psi_e->data[nm1d2] = anew + (real_T)nm1d2;
        psi_e->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
      }
    }
  }

  emxInit_real_T(&c_st, &K, 2, &d_emlrtRTEI, true);
  i2 = K->size[0] * K->size[1];
  st.site = &b_emlrtRSI;
  d0 = mpower(&st, psi_e->size[1], dim);
  if (!(d0 > 0.0)) {
    emlrtNonNegativeCheckR2012b(d0, &emlrtDCI, sp);
  }

  if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
    emlrtIntegerCheckR2012b(d0, &b_emlrtDCI, sp);
  }

  K->size[0] = (int32_T)d0;
  if (!(dim > 0.0)) {
    emlrtNonNegativeCheckR2012b(dim, &c_emlrtDCI, sp);
  }

  if (dim != (int32_T)muDoubleScalarFloor(dim)) {
    emlrtIntegerCheckR2012b(dim, &d_emlrtDCI, sp);
  }

  K->size[1] = (int32_T)dim;
  emxEnsureCapacity(sp, (emxArray__common *)K, i2, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  st.site = &b_emlrtRSI;
  d0 = mpower(&st, psi_e->size[1], dim);
  if (!(d0 > 0.0)) {
    emlrtNonNegativeCheckR2012b(d0, &emlrtDCI, sp);
  }

  if (d0 != (int32_T)muDoubleScalarFloor(d0)) {
    emlrtIntegerCheckR2012b(d0, &b_emlrtDCI, sp);
  }

  if (!(dim > 0.0)) {
    emlrtNonNegativeCheckR2012b(dim, &c_emlrtDCI, sp);
  }

  anew = dim;
  if (anew != (int32_T)muDoubleScalarFloor(anew)) {
    emlrtIntegerCheckR2012b(anew, &d_emlrtDCI, sp);
  }

  loop_ub = (int32_T)d0 * (int32_T)anew;
  for (i2 = 0; i2 < loop_ub; i2++) {
    K->data[i2] = 0.0;
  }

  st.site = &c_emlrtRSI;
  b_st.site = &s_emlrtRSI;
  c_st.site = &t_emlrtRSI;
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

  d_st.site = &u_emlrtRSI;
  if (!n_too_large) {
  } else {
    emlrtErrorWithMessageIdR2012b(&d_st, &u_emlrtRTEI, "Coder:MATLAB:pmaxsize",
      0);
  }

  i2 = psi_e->size[0] * psi_e->size[1];
  psi_e->size[0] = 1;
  psi_e->size[1] = n;
  emxEnsureCapacity(&c_st, (emxArray__common *)psi_e, i2, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  if (n > 0) {
    psi_e->data[0] = anew;
    if (n > 1) {
      psi_e->data[n - 1] = apnd;
      i2 = n - 1;
      nm1d2 = asr_s32(i2, 1U);
      d_st.site = &v_emlrtRSI;
      for (k = 1; k < nm1d2; k++) {
        psi_e->data[k] = anew + (real_T)k;
        psi_e->data[(n - k) - 1] = apnd - (real_T)k;
      }

      if (nm1d2 << 1 == n - 1) {
        psi_e->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        psi_e->data[nm1d2] = anew + (real_T)nm1d2;
        psi_e->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
      }
    }
  }

  st.site = &c_emlrtRSI;
  d0 = mpower(&st, psi_e->size[1], dim);
  emlrtForLoopVectorCheckR2012b(1.0, 1.0, d0, mxDOUBLE_CLASS, (int32_T)d0,
    &p_emlrtRTEI, sp);
  i = 0;
  emxInit_real_T(sp, &phi_e, 2, &i_emlrtRTEI, true);
  emxInit_int32_T(sp, &r0, 1, &b_emlrtRTEI, true);
  while (i <= (int32_T)d0 - 1) {
    i2 = K->size[0];
    i3 = i + 1;
    if (!((i3 >= 1) && (i3 <= i2))) {
      emlrtDynamicBoundsCheckR2012b(i3, 1, i2, &b_emlrtBCI, sp);
    }

    loop_ub = K->size[1];
    i2 = r0->size[0];
    r0->size[0] = loop_ub;
    emxEnsureCapacity(sp, (emxArray__common *)r0, i2, (int32_T)sizeof(int32_T),
                      &b_emlrtRTEI);
    for (i2 = 0; i2 < loop_ub; i2++) {
      r0->data[i2] = i2;
    }

    st.site = &d_emlrtRSI;
    b_st.site = &s_emlrtRSI;
    c_st.site = &t_emlrtRSI;
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

    d_st.site = &u_emlrtRSI;
    if (!n_too_large) {
    } else {
      emlrtErrorWithMessageIdR2012b(&d_st, &u_emlrtRTEI, "Coder:MATLAB:pmaxsize",
        0);
    }

    i2 = psi_e->size[0] * psi_e->size[1];
    psi_e->size[0] = 1;
    psi_e->size[1] = n;
    emxEnsureCapacity(&c_st, (emxArray__common *)psi_e, i2, (int32_T)sizeof
                      (real_T), &b_emlrtRTEI);
    if (n > 0) {
      psi_e->data[0] = anew;
      if (n > 1) {
        psi_e->data[n - 1] = apnd;
        i2 = n - 1;
        nm1d2 = asr_s32(i2, 1U);
        d_st.site = &v_emlrtRSI;
        for (k = 1; k < nm1d2; k++) {
          psi_e->data[k] = anew + (real_T)k;
          psi_e->data[(n - k) - 1] = apnd - (real_T)k;
        }

        if (nm1d2 << 1 == n - 1) {
          psi_e->data[nm1d2] = (anew + apnd) / 2.0;
        } else {
          psi_e->data[nm1d2] = anew + (real_T)nm1d2;
          psi_e->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
        }
      }
    }

    st.site = &d_emlrtRSI;
    permn2(&st, psi_e, dim, 1.0 + (real_T)i, phi_e);
    iv0[0] = 1;
    iv0[1] = r0->size[0];
    emlrtSubAssignSizeCheckR2012b(iv0, 2, *(int32_T (*)[2])phi_e->size, 2,
      &emlrtECI, sp);
    loop_ub = phi_e->size[1];
    for (i2 = 0; i2 < loop_ub; i2++) {
      K->data[i + K->size[0] * r0->data[i2]] = phi_e->data[phi_e->size[0] * i2];
    }

    i++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  emxInit_real_T(sp, &X, 2, &e_emlrtRTEI, true);

  /* K = permn(k_min:k_max,dim); */
  k_sz = K->size[0];
  i2 = X->size[0] * X->size[1];
  st.site = &e_emlrtRSI;
  X->size[0] = (int32_T)mpower(&st, grid_x->size[1], dim);
  X->size[1] = (int32_T)dim;
  emxEnsureCapacity(sp, (emxArray__common *)X, i2, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  st.site = &e_emlrtRSI;
  d0 = mpower(&st, grid_x->size[1], dim);
  loop_ub = (int32_T)d0 * (int32_T)dim;
  for (i2 = 0; i2 < loop_ub; i2++) {
    X->data[i2] = 0.0;
  }

  st.site = &f_emlrtRSI;
  d0 = mpower(&st, grid_x->size[1], dim);
  emlrtForLoopVectorCheckR2012b(1.0, 1.0, d0, mxDOUBLE_CLASS, (int32_T)d0,
    &q_emlrtRTEI, sp);
  i = 0;
  emxInit_real_T(sp, &b_grid_x, 2, &b_emlrtRTEI, true);
  while (i <= (int32_T)d0 - 1) {
    i2 = X->size[0];
    i3 = i + 1;
    if (!((i3 >= 1) && (i3 <= i2))) {
      emlrtDynamicBoundsCheckR2012b(i3, 1, i2, &c_emlrtBCI, sp);
    }

    loop_ub = X->size[1];
    i2 = r0->size[0];
    r0->size[0] = loop_ub;
    emxEnsureCapacity(sp, (emxArray__common *)r0, i2, (int32_T)sizeof(int32_T),
                      &b_emlrtRTEI);
    for (i2 = 0; i2 < loop_ub; i2++) {
      r0->data[i2] = i2;
    }

    i2 = b_grid_x->size[0] * b_grid_x->size[1];
    b_grid_x->size[0] = 1;
    b_grid_x->size[1] = grid_x->size[1];
    emxEnsureCapacity(sp, (emxArray__common *)b_grid_x, i2, (int32_T)sizeof
                      (real_T), &b_emlrtRTEI);
    loop_ub = grid_x->size[0] * grid_x->size[1];
    for (i2 = 0; i2 < loop_ub; i2++) {
      b_grid_x->data[i2] = grid_x->data[i2];
    }

    st.site = &g_emlrtRSI;
    permn2(&st, b_grid_x, dim, 1.0 + (real_T)i, psi_e);
    iv1[0] = 1;
    iv1[1] = r0->size[0];
    emlrtSubAssignSizeCheckR2012b(iv1, 2, *(int32_T (*)[2])psi_e->size, 2,
      &b_emlrtECI, sp);
    loop_ub = psi_e->size[1];
    for (i2 = 0; i2 < loop_ub; i2++) {
      X->data[i + X->size[0] * r0->data[i2]] = psi_e->data[psi_e->size[0] * i2];
    }

    i++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  emxFree_real_T(&b_grid_x);
  emxFree_int32_T(&r0);

  /* X = permn(grid_x,dim); */
  x_sz = X->size[0];
  st.site = &h_emlrtRSI;
  b_st.site = &s_emlrtRSI;
  c_st.site = &t_emlrtRSI;
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

  d_st.site = &u_emlrtRSI;
  if (!n_too_large) {
  } else {
    emlrtErrorWithMessageIdR2012b(&d_st, &u_emlrtRTEI, "Coder:MATLAB:pmaxsize",
      0);
  }

  i2 = psi_e->size[0] * psi_e->size[1];
  psi_e->size[0] = 1;
  psi_e->size[1] = n;
  emxEnsureCapacity(&c_st, (emxArray__common *)psi_e, i2, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  if (n > 0) {
    psi_e->data[0] = anew;
    if (n > 1) {
      psi_e->data[n - 1] = apnd;
      i2 = n - 1;
      nm1d2 = asr_s32(i2, 1U);
      d_st.site = &v_emlrtRSI;
      for (k = 1; k < nm1d2; k++) {
        psi_e->data[k] = anew + (real_T)k;
        psi_e->data[(n - k) - 1] = apnd - (real_T)k;
      }

      if (nm1d2 << 1 == n - 1) {
        psi_e->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        psi_e->data[nm1d2] = anew + (real_T)nm1d2;
        psi_e->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
      }
    }
  }

  i2 = D_ejk->size[0] * D_ejk->size[1] * D_ejk->size[2];
  D_ejk->size[0] = E_dash->size[0];
  D_ejk->size[1] = psi_e->size[1];
  D_ejk->size[2] = K->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)D_ejk, i2, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  loop_ub = E_dash->size[0] * psi_e->size[1] * K->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    D_ejk->data[i2] = 0.0;
  }

  i2 = C_00k->size[0] * C_00k->size[1] * C_00k->size[2];
  C_00k->size[0] = 1;
  C_00k->size[1] = 1;
  C_00k->size[2] = K->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)C_00k, i2, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  loop_ub = K->size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    C_00k->data[i2] = 0.0;
  }

  emxInit_real_T(sp, &phis, 2, &f_emlrtRTEI, true);
  i2 = phis->size[0] * phis->size[1];
  phis->size[0] = 1;
  phis->size[1] = (int32_T)dim;
  emxEnsureCapacity(sp, (emxArray__common *)phis, i2, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  loop_ub = (int32_T)dim;
  for (i2 = 0; i2 < loop_ub; i2++) {
    phis->data[i2] = 0.0;
  }

  emxInit_real_T(sp, &psis, 2, &g_emlrtRTEI, true);
  i2 = psis->size[0] * psis->size[1];
  psis->size[0] = 1;
  psis->size[1] = (int32_T)dim;
  emxEnsureCapacity(sp, (emxArray__common *)psis, i2, (int32_T)sizeof(real_T),
                    &b_emlrtRTEI);
  loop_ub = (int32_T)dim;
  for (i2 = 0; i2 < loop_ub; i2++) {
    psis->data[i2] = 0.0;
  }

  /* % */
  /* compute C_00k */
  k_dims = 1;
  emxInit_real_T1(sp, &x, 1, &h_emlrtRTEI, true);
  emxInit_real_T1(sp, &r1, 1, &b_emlrtRTEI, true);
  while (k_dims - 1 <= k_sz - 1) {
    summation_C = 0.0;
    x_dims = 0;
    while (x_dims <= x_sz - 1) {
      loop_ub = X->size[1];
      i2 = X->size[0];
      i3 = 1 + x_dims;
      if (!((i3 >= 1) && (i3 <= i2))) {
        emlrtDynamicBoundsCheckR2012b(i3, 1, i2, &d_emlrtBCI, sp);
      }

      i2 = x->size[0];
      x->size[0] = loop_ub;
      emxEnsureCapacity(sp, (emxArray__common *)x, i2, (int32_T)sizeof(real_T),
                        &b_emlrtRTEI);
      for (i2 = 0; i2 < loop_ub; i2++) {
        x->data[i2] = X->data[(i3 + X->size[0] * i2) - 1];
      }

      loop_ub = K->size[1];
      i2 = K->size[0];
      if (!((k_dims >= 1) && (k_dims <= i2))) {
        emlrtDynamicBoundsCheckR2012b(k_dims, 1, i2, &e_emlrtBCI, sp);
      }

      i2 = r1->size[0];
      r1->size[0] = loop_ub;
      emxEnsureCapacity(sp, (emxArray__common *)r1, i2, (int32_T)sizeof(real_T),
                        &b_emlrtRTEI);
      for (i2 = 0; i2 < loop_ub; i2++) {
        r1->data[i2] = K->data[(k_dims + K->size[0] * i2) - 1];
      }

      i2 = x->size[0];
      i3 = r1->size[0];
      if (i2 != i3) {
        emlrtSizeEqCheck1DR2012b(i2, i3, &c_emlrtECI, sp);
      }

      i2 = x->size[0];
      emxEnsureCapacity(sp, (emxArray__common *)x, i2, (int32_T)sizeof(real_T),
                        &b_emlrtRTEI);
      loop_ub = x->size[0];
      for (i2 = 0; i2 < loop_ub; i2++) {
        x->data[i2] -= r1->data[i2];
      }

      /* [phis,~] = arrayfun(@(t) MeyerWavelet(t),x); */
      /* phis = (2^0)*phis'; */
      emlrtForLoopVectorCheckR2012b(1.0, 1.0, dim, mxDOUBLE_CLASS, (int32_T)dim,
        &r_emlrtRTEI, sp);
      dimen = 1;
      while (dimen - 1 <= (int32_T)dim - 1) {
        i2 = x->size[0];
        if (!((dimen >= 1) && (dimen <= i2))) {
          emlrtDynamicBoundsCheckR2012b(dimen, 1, i2, &s_emlrtBCI, sp);
        }

        i2 = phis->size[1];
        if (!((dimen >= 1) && (dimen <= i2))) {
          emlrtDynamicBoundsCheckR2012b(dimen, 1, i2, &t_emlrtBCI, sp);
        }

        st.site = &i_emlrtRSI;
        phis->data[dimen - 1] = MeyerWavelet(x->data[dimen - 1]);
        dimen++;
        if (*emlrtBreakCheckR2012bFlagVar != 0) {
          emlrtBreakCheckR2012b(sp);
        }
      }

      st.site = &j_emlrtRSI;
      bigPhi_00k_x = prod(&st, phis);
      i2 = dist_array_xy->size[0] * dist_array_xy->size[1];
      i3 = x_dims + 1;
      if (!((i3 >= 1) && (i3 <= i2))) {
        emlrtDynamicBoundsCheckR2012b(i3, 1, i2, &f_emlrtBCI, sp);
      }

      st.site = &k_emlrtRSI;
      summation_C += mpower(&st, dx, dim) * dist_array_xy->data[x_dims] *
        bigPhi_00k_x;

      /* check use of dim and dx here */
      x_dims++;
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b(sp);
      }
    }

    i2 = C_00k->size[2];
    if (!((k_dims >= 1) && (k_dims <= i2))) {
      emlrtDynamicBoundsCheckR2012b(k_dims, 1, i2, &r_emlrtBCI, sp);
    }

    C_00k->data[C_00k->size[0] * C_00k->size[1] * (k_dims - 1)] = summation_C;
    k_dims++;
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b(sp);
    }
  }

  i2 = (i1 - i0) - 1;
  e = 0;
  emxInit_real_T(sp, &b_phi_e, 2, &b_emlrtRTEI, true);
  emxInit_real_T(sp, &b_E_dash, 2, &b_emlrtRTEI, true);
  emxInit_real_T(sp, &c_E_dash, 2, &b_emlrtRTEI, true);
  emxInit_real_T(sp, &d_E_dash, 2, &b_emlrtRTEI, true);
  emxInit_real_T(sp, &e_E_dash, 2, &b_emlrtRTEI, true);
  while (e <= i2) {
    j_ix = 0.0;
    i3 = (int32_T)(j_max + (1.0 - j_min));
    emlrtForLoopVectorCheckR2012b(j_min, 1.0, j_max, mxDOUBLE_CLASS, i3,
      &s_emlrtRTEI, sp);
    j = 0;
    while (j <= i3 - 1) {
      b_j = j_min + (real_T)j;
      j_ix++;
      k_dims = 0;
      while (k_dims <= k_sz - 1) {
        /* k along each dim */
        summation_D = 0.0;
        x_dims = 0;
        while (x_dims <= x_sz - 1) {
          if (viz != 0.0) {
            st.site = &l_emlrtRSI;
            b_st.site = &s_emlrtRSI;
            c_st.site = &t_emlrtRSI;
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

            d_st.site = &u_emlrtRSI;
            if (!n_too_large) {
            } else {
              emlrtErrorWithMessageIdR2012b(&d_st, &u_emlrtRTEI,
                "Coder:MATLAB:pmaxsize", 0);
            }

            i4 = psi_e->size[0] * psi_e->size[1];
            psi_e->size[0] = 1;
            psi_e->size[1] = n;
            emxEnsureCapacity(&c_st, (emxArray__common *)psi_e, i4, (int32_T)
                              sizeof(real_T), &b_emlrtRTEI);
            if (n > 0) {
              psi_e->data[0] = anew;
              if (n > 1) {
                psi_e->data[n - 1] = apnd;
                i4 = n - 1;
                nm1d2 = asr_s32(i4, 1U);
                d_st.site = &v_emlrtRSI;
                for (k = 1; k < nm1d2; k++) {
                  psi_e->data[k] = anew + (real_T)k;
                  psi_e->data[(n - k) - 1] = apnd - (real_T)k;
                }

                if (nm1d2 << 1 == n - 1) {
                  psi_e->data[nm1d2] = (anew + apnd) / 2.0;
                } else {
                  psi_e->data[nm1d2] = anew + (real_T)nm1d2;
                  psi_e->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
                }
              }
            }

            emlrtAssertMATLABThread(sp, &emlrtRTEI);
            dv0[0] = (1.0 + (real_T)e) / (real_T)(i1 - i0);
            dv0[1] = j_ix / (real_T)psi_e->size[1];
            dv0[2] = (1.0 + (real_T)k_dims) / (real_T)k_sz;
            dv0[3] = (1.0 + (real_T)x_dims) / (real_T)x_sz;
            emlrtDisplayR2012b(emlrt_marshallOut(dv0), "ans", &emlrtRTEI, sp);
          }

          st.site = &m_emlrtRSI;
          anew = mpower(&st, 2.0, b_j);
          i4 = X->size[0];
          n = x_dims + 1;
          if (!((n >= 1) && (n <= i4))) {
            emlrtDynamicBoundsCheckR2012b(n, 1, i4, &g_emlrtBCI, sp);
          }

          loop_ub = X->size[1];
          i4 = x->size[0];
          x->size[0] = loop_ub;
          emxEnsureCapacity(sp, (emxArray__common *)x, i4, (int32_T)sizeof
                            (real_T), &b_emlrtRTEI);
          for (i4 = 0; i4 < loop_ub; i4++) {
            x->data[i4] = anew * X->data[x_dims + X->size[0] * i4];
          }

          loop_ub = K->size[1];
          i4 = K->size[0];
          if (!((k_dims + 1 >= 1) && (k_dims + 1 <= i4))) {
            emlrtDynamicBoundsCheckR2012b(k_dims + 1, 1, i4, &h_emlrtBCI, sp);
          }

          k = k_dims + 1;
          i4 = r1->size[0];
          r1->size[0] = loop_ub;
          emxEnsureCapacity(sp, (emxArray__common *)r1, i4, (int32_T)sizeof
                            (real_T), &b_emlrtRTEI);
          for (i4 = 0; i4 < loop_ub; i4++) {
            r1->data[i4] = K->data[(k + K->size[0] * i4) - 1];
          }

          i4 = x->size[0];
          n = r1->size[0];
          if (i4 != n) {
            emlrtSizeEqCheck1DR2012b(i4, n, &d_emlrtECI, sp);
          }

          i4 = x->size[0];
          emxEnsureCapacity(sp, (emxArray__common *)x, i4, (int32_T)sizeof
                            (real_T), &b_emlrtRTEI);
          loop_ub = x->size[0];
          for (i4 = 0; i4 < loop_ub; i4++) {
            x->data[i4] -= r1->data[i4];
          }

          emlrtForLoopVectorCheckR2012b(1.0, 1.0, dim, mxDOUBLE_CLASS, (int32_T)
            dim, &t_emlrtRTEI, sp);
          dimen = 1;
          while (dimen - 1 <= (int32_T)dim - 1) {
            i4 = x->size[0];
            if (!((dimen >= 1) && (dimen <= i4))) {
              emlrtDynamicBoundsCheckR2012b(dimen, 1, i4, &o_emlrtBCI, sp);
            }

            i4 = phis->size[1];
            if (!((dimen >= 1) && (dimen <= i4))) {
              emlrtDynamicBoundsCheckR2012b(dimen, 1, i4, &p_emlrtBCI, sp);
            }

            i4 = psis->size[1];
            if (!((dimen >= 1) && (dimen <= i4))) {
              emlrtDynamicBoundsCheckR2012b(dimen, 1, i4, &q_emlrtBCI, sp);
            }

            st.site = &n_emlrtRSI;
            b_MeyerWavelet(x->data[dimen - 1], &phis->data[dimen - 1],
                           &psis->data[dimen - 1]);
            dimen++;
            if (*emlrtBreakCheckR2012bFlagVar != 0) {
              emlrtBreakCheckR2012b(sp);
            }
          }

          /* [phis,psis] = arrayfun(@(t) MeyerWavelet(t),x); */
          st.site = &o_emlrtRSI;
          anew = mpower(&st, 2.0, b_j);
          i4 = phis->size[0] * phis->size[1];
          phis->size[0] = 1;
          emxEnsureCapacity(sp, (emxArray__common *)phis, i4, (int32_T)sizeof
                            (real_T), &b_emlrtRTEI);
          k = phis->size[0];
          nm1d2 = phis->size[1];
          loop_ub = k * nm1d2;
          for (i4 = 0; i4 < loop_ub; i4++) {
            phis->data[i4] *= anew;
          }

          st.site = &p_emlrtRSI;
          anew = mpower(&st, 2.0, b_j);
          i4 = psis->size[0] * psis->size[1];
          psis->size[0] = 1;
          emxEnsureCapacity(sp, (emxArray__common *)psis, i4, (int32_T)sizeof
                            (real_T), &b_emlrtRTEI);
          k = psis->size[0];
          nm1d2 = psis->size[1];
          loop_ub = k * nm1d2;
          for (i4 = 0; i4 < loop_ub; i4++) {
            psis->data[i4] *= anew;
          }

          /* keyboard */
          i4 = i1 - i0;
          n = e + 1;
          if (!((n >= 1) && (n <= i4))) {
            emlrtDynamicBoundsCheckR2012b(n, 1, i4, &i_emlrtBCI, sp);
          }

          loop_ub = E_dash->size[1];
          nm1d2 = E_dash->size[1];
          i4 = b_E_dash->size[0] * b_E_dash->size[1];
          b_E_dash->size[0] = i1 - i0;
          b_E_dash->size[1] = nm1d2;
          emxEnsureCapacity(sp, (emxArray__common *)b_E_dash, i4, (int32_T)
                            sizeof(real_T), &b_emlrtRTEI);
          for (i4 = 0; i4 < nm1d2; i4++) {
            k = i1 - i0;
            for (n = 0; n < k; n++) {
              b_E_dash->data[n + b_E_dash->size[0] * i4] = E_dash->data[((i0 + n)
                + E_dash->size[0] * i4) - 1];
            }
          }

          i4 = c_E_dash->size[0] * c_E_dash->size[1];
          c_E_dash->size[0] = 1;
          c_E_dash->size[1] = loop_ub;
          emxEnsureCapacity(sp, (emxArray__common *)c_E_dash, i4, (int32_T)
                            sizeof(real_T), &b_emlrtRTEI);
          for (i4 = 0; i4 < loop_ub; i4++) {
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
            emlrtSizeEqCheckNDR2012b(&f_E_dash[0], &b_phis[0], &e_emlrtECI, sp);
          }

          loop_ub = E_dash->size[1];
          i4 = phi_e->size[0] * phi_e->size[1];
          phi_e->size[0] = 1;
          phi_e->size[1] = loop_ub;
          emxEnsureCapacity(sp, (emxArray__common *)phi_e, i4, (int32_T)sizeof
                            (real_T), &b_emlrtRTEI);
          for (i4 = 0; i4 < loop_ub; i4++) {
            phi_e->data[phi_e->size[0] * i4] = (1.0 - E->data[e + E->size[0] *
              i4]) * phis->data[phis->size[0] * i4];
          }

          i4 = i1 - i0;
          n = e + 1;
          if (!((n >= 1) && (n <= i4))) {
            emlrtDynamicBoundsCheckR2012b(n, 1, i4, &j_emlrtBCI, sp);
          }

          loop_ub = E_dash->size[1];
          nm1d2 = E_dash->size[1];
          i4 = d_E_dash->size[0] * d_E_dash->size[1];
          d_E_dash->size[0] = i1 - i0;
          d_E_dash->size[1] = nm1d2;
          emxEnsureCapacity(sp, (emxArray__common *)d_E_dash, i4, (int32_T)
                            sizeof(real_T), &b_emlrtRTEI);
          for (i4 = 0; i4 < nm1d2; i4++) {
            k = i1 - i0;
            for (n = 0; n < k; n++) {
              d_E_dash->data[n + d_E_dash->size[0] * i4] = E_dash->data[((i0 + n)
                + E_dash->size[0] * i4) - 1];
            }
          }

          i4 = e_E_dash->size[0] * e_E_dash->size[1];
          e_E_dash->size[0] = 1;
          e_E_dash->size[1] = loop_ub;
          emxEnsureCapacity(sp, (emxArray__common *)e_E_dash, i4, (int32_T)
                            sizeof(real_T), &b_emlrtRTEI);
          for (i4 = 0; i4 < loop_ub; i4++) {
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
            emlrtSizeEqCheckNDR2012b(&g_E_dash[0], &b_psis[0], &f_emlrtECI, sp);
          }

          loop_ub = E_dash->size[1];
          i4 = psi_e->size[0] * psi_e->size[1];
          psi_e->size[0] = 1;
          psi_e->size[1] = loop_ub;
          emxEnsureCapacity(sp, (emxArray__common *)psi_e, i4, (int32_T)sizeof
                            (real_T), &b_emlrtRTEI);
          for (i4 = 0; i4 < loop_ub; i4++) {
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
            emlrtSizeEqCheckNDR2012b(&c_phi_e[0], &b_psi_e[0], &g_emlrtECI, sp);
          }

          i4 = b_phi_e->size[0] * b_phi_e->size[1];
          b_phi_e->size[0] = 1;
          b_phi_e->size[1] = phi_e->size[1];
          emxEnsureCapacity(sp, (emxArray__common *)b_phi_e, i4, (int32_T)sizeof
                            (real_T), &b_emlrtRTEI);
          loop_ub = phi_e->size[0] * phi_e->size[1];
          for (i4 = 0; i4 < loop_ub; i4++) {
            b_phi_e->data[i4] = phi_e->data[i4] + psi_e->data[i4];
          }

          st.site = &q_emlrtRSI;
          bigPsi_ejk_x = prod(&st, b_phi_e);

          /*  check if vectorization preserves locations in this % */
          i4 = dist_array_xy->size[0] * dist_array_xy->size[1];
          n = x_dims + 1;
          if (!((n >= 1) && (n <= i4))) {
            emlrtDynamicBoundsCheckR2012b(n, 1, i4, &k_emlrtBCI, sp);
          }

          st.site = &r_emlrtRSI;
          summation_D += mpower(&st, dx, dim) * dist_array_xy->data[x_dims] *
            bigPsi_ejk_x;

          /* check use of dim and dx here */
          x_dims++;
          if (*emlrtBreakCheckR2012bFlagVar != 0) {
            emlrtBreakCheckR2012b(sp);
          }
        }

        i4 = D_ejk->size[0];
        n = 1 + e;
        if (!((n >= 1) && (n <= i4))) {
          emlrtDynamicBoundsCheckR2012b(n, 1, i4, &l_emlrtBCI, sp);
        }

        i4 = D_ejk->size[1];
        k = (int32_T)j_ix;
        if (!((k >= 1) && (k <= i4))) {
          emlrtDynamicBoundsCheckR2012b(k, 1, i4, &m_emlrtBCI, sp);
        }

        i4 = D_ejk->size[2];
        if (!((k_dims + 1 >= 1) && (k_dims + 1 <= i4))) {
          emlrtDynamicBoundsCheckR2012b(k_dims + 1, 1, i4, &n_emlrtBCI, sp);
        }

        D_ejk->data[((n + D_ejk->size[0] * (k - 1)) + D_ejk->size[0] *
                     D_ejk->size[1] * k_dims) - 1] = summation_D;
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
  emxFree_real_T(&x);
  emxFree_real_T(&psis);
  emxFree_real_T(&phis);
  emxFree_real_T(&X);
  emxFree_real_T(&K);
  emxFree_real_T(&E);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (alt_getCoefficientsVector_genable.c) */
