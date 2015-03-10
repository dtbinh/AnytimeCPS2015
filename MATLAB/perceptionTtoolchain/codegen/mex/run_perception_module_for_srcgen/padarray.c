/*
 * padarray.c
 *
 * Code generation for function 'padarray'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "padarray.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "mod.h"
#include "eml_warning.h"
#include "colon.h"
#include "validateattributes.h"
#include "run_perception_module_for_srcgen_mexutil.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRSInfo tb_emlrtRSI = { 6, "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m"
};

static emlrtRSInfo ub_emlrtRSI = { 321, "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m"
};

static emlrtRSInfo wb_emlrtRSI = { 34, "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m"
};

static emlrtRSInfo xb_emlrtRSI = { 434, "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m"
};

static emlrtRSInfo yb_emlrtRSI = { 21, "colon",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" };

static emlrtRSInfo ac_emlrtRSI = { 79, "colon",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" };

static emlrtRSInfo bc_emlrtRSI = { 291, "colon",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" };

static emlrtRSInfo cc_emlrtRSI = { 283, "colon",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" };

static emlrtRSInfo dc_emlrtRSI = { 520, "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m"
};

static emlrtRSInfo ec_emlrtRSI = { 506, "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m"
};

static emlrtRTEInfo h_emlrtRTEI = { 500, 5, "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m"
};

static emlrtRTEInfo i_emlrtRTEI = { 46, 9, "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m"
};

static emlrtRTEInfo j_emlrtRTEI = { 284, 1, "colon",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" };

static emlrtRTEInfo k_emlrtRTEI = { 1, 14, "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m"
};

static emlrtRTEInfo l_emlrtRTEI = { 510, 9, "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m"
};

static emlrtBCInfo m_emlrtBCI = { -1, -1, 522, 14, "", "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m",
  0 };

static emlrtECInfo b_emlrtECI = { -1, 522, 9, "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m"
};

static emlrtBCInfo n_emlrtBCI = { -1, -1, 49, 19, "", "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m",
  0 };

static emlrtBCInfo o_emlrtBCI = { -1, -1, 49, 21, "", "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m",
  0 };

static emlrtBCInfo p_emlrtBCI = { 1, 1200, 49, 28, "", "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m",
  0 };

static emlrtBCInfo q_emlrtBCI = { -1, -1, 49, 33, "", "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m",
  0 };

static emlrtBCInfo r_emlrtBCI = { 1, 1600, 49, 38, "", "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m",
  0 };

static emlrtBCInfo s_emlrtBCI = { -1, -1, 49, 43, "", "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m",
  0 };

static emlrtBCInfo t_emlrtBCI = { -1, -1, 520, 18, "", "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m",
  0 };

static emlrtDCInfo b_emlrtDCI = { 520, 18, "padarray",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\padarray.m",
  1 };

/* Function Definitions */
void padarray(const emlrtStack *sp, const boolean_T varargin_1[1920000], const
              real_T varargin_2[2], emxArray_boolean_T *b)
{
  int32_T sizeB[2];
  real_T b_varargin_2[2];
  real_T b_varargin_1[2];
  int32_T i6;
  int32_T ixstart;
  real_T mtmp;
  int32_T ix;
  boolean_T exitg1;
  emxArray_int32_T *idxA;
  int32_T sizeIdxDir[2];
  emxArray_uint32_T *idxDir;
  emxArray_int32_T *r1;
  emxArray_real_T *y;
  emxArray_real_T *r2;
  emxArray_int32_T *b_idxDir;
  int32_T k;
  boolean_T n_too_large;
  real_T anew;
  int32_T n;
  real_T y_data[1600];
  int32_T b_n;
  real_T b_y_data[1600];
  int32_T dimNums_size_idx_1;
  uint32_T u0;
  uint32_T dimNums_data[3200];
  real_T apnd;
  real_T ndbl;
  real_T cdiff;
  real_T absa;
  real_T absb;
  const mxArray *b_y;
  static const int32_T iv12[2] = { 1, 21 };

  const mxArray *m9;
  char_T cv23[21];
  int32_T i;
  static const char_T cv24[21] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 'p', 'm', 'a', 'x', 's', 'i', 'z', 'e' };

  int32_T i7;
  int32_T iv13[1];
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
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
  h_st.prev = &f_st;
  h_st.tls = f_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);
  st.site = &tb_emlrtRSI;
  b_st.site = &ub_emlrtRSI;
  validateattributes(&b_st, varargin_2);
  st.site = &wb_emlrtRSI;
  b_st.site = &xb_emlrtRSI;
  b_varargin_2[0] = varargin_2[0];
  b_varargin_2[1] = varargin_2[1];
  for (i6 = 0; i6 < 2; i6++) {
    b_varargin_1[i6] = 2.0 * b_varargin_2[i6] + (1200.0 + 400.0 * (real_T)i6);
  }

  ixstart = 1;
  mtmp = b_varargin_1[0];
  if (muDoubleScalarIsNaN(b_varargin_1[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 3)) {
      ixstart = 2;
      if (!muDoubleScalarIsNaN(b_varargin_1[1])) {
        mtmp = b_varargin_1[1];
        exitg1 = true;
      } else {
        ix = 3;
      }
    }
  }

  if ((ixstart < 2) && (b_varargin_1[1] > mtmp)) {
    mtmp = b_varargin_1[1];
  }

  b_emxInit_int32_T(&b_st, &idxA, 2, &k_emlrtRTEI, true);
  i6 = idxA->size[0] * idxA->size[1];
  idxA->size[0] = (int32_T)mtmp;
  idxA->size[1] = 2;
  emxEnsureCapacity(&b_st, (emxArray__common *)idxA, i6, (int32_T)sizeof(int32_T),
                    &h_emlrtRTEI);
  emxInit_uint32_T(&b_st, &idxDir, 2, &l_emlrtRTEI, true);
  emxInit_int32_T(&b_st, &r1, 1, &k_emlrtRTEI, true);
  b_emxInit_real_T(&b_st, &y, 2, &k_emlrtRTEI, true);
  b_emxInit_real_T(&b_st, &r2, 2, &k_emlrtRTEI, true);
  b_emxInit_int32_T(&b_st, &b_idxDir, 2, &k_emlrtRTEI, true);
  for (k = 0; k < 2; k++) {
    c_st.site = &ec_emlrtRSI;
    d_st.site = &yb_emlrtRSI;
    e_st.site = &ac_emlrtRSI;
    float_colon_length(1200.0 + 400.0 * (real_T)k, &n, &anew, &mtmp,
                       &n_too_large);
    f_st.site = &cc_emlrtRSI;
    assert_pmaxsize(&f_st, !n_too_large);
    y_data[0] = anew;
    if (n > 1) {
      y_data[n - 1] = mtmp;
      i6 = n - 1;
      ixstart = (int32_T)((uint32_T)i6 >> 1);
      f_st.site = &bc_emlrtRSI;
      for (ix = 1; ix < ixstart; ix++) {
        y_data[ix] = anew + (real_T)ix;
        y_data[(n - ix) - 1] = mtmp - (real_T)ix;
      }

      if (ixstart << 1 == n - 1) {
        y_data[ixstart] = (anew + mtmp) / 2.0;
      } else {
        y_data[ixstart] = anew + (real_T)ixstart;
        y_data[ixstart + 1] = mtmp - (real_T)ixstart;
      }
    }

    c_st.site = &ec_emlrtRSI;
    d_st.site = &ac_emlrtRSI;
    b_float_colon_length(1200.0 + 400.0 * (real_T)k, &b_n, &anew, &mtmp,
                         &n_too_large);
    e_st.site = &cc_emlrtRSI;
    assert_pmaxsize(&e_st, !n_too_large);
    b_y_data[0] = anew;
    if (b_n > 1) {
      b_y_data[b_n - 1] = mtmp;
      i6 = b_n - 1;
      ixstart = (int32_T)((uint32_T)i6 >> 1);
      e_st.site = &bc_emlrtRSI;
      for (ix = 1; ix < ixstart; ix++) {
        b_y_data[ix] = anew + -(real_T)ix;
        b_y_data[(b_n - ix) - 1] = mtmp - (-(real_T)ix);
      }

      if (ixstart << 1 == b_n - 1) {
        b_y_data[ixstart] = (anew + mtmp) / 2.0;
      } else {
        b_y_data[ixstart] = anew + -(real_T)ixstart;
        b_y_data[ixstart + 1] = mtmp - (-(real_T)ixstart);
      }
    }

    dimNums_size_idx_1 = n + b_n;
    for (i6 = 0; i6 < n; i6++) {
      mtmp = muDoubleScalarRound(y_data[i6]);
      if (mtmp < 4.294967296E+9) {
        if (mtmp >= 0.0) {
          u0 = (uint32_T)mtmp;
        } else {
          u0 = 0U;
        }
      } else if (mtmp >= 4.294967296E+9) {
        u0 = MAX_uint32_T;
      } else {
        u0 = 0U;
      }

      dimNums_data[i6] = u0;
    }

    for (i6 = 0; i6 < b_n; i6++) {
      mtmp = muDoubleScalarRound(b_y_data[i6]);
      if (mtmp < 4.294967296E+9) {
        if (mtmp >= 0.0) {
          u0 = (uint32_T)mtmp;
        } else {
          u0 = 0U;
        }
      } else if (mtmp >= 4.294967296E+9) {
        u0 = MAX_uint32_T;
      } else {
        u0 = 0U;
      }

      dimNums_data[i6 + n] = u0;
    }

    c_st.site = &dc_emlrtRSI;
    mtmp = ((1200.0 + 400.0 * (real_T)k) + varargin_2[k]) - 1.0;
    d_st.site = &yb_emlrtRSI;
    e_st.site = &ac_emlrtRSI;
    if (muDoubleScalarIsNaN(-varargin_2[k]) || muDoubleScalarIsNaN(mtmp)) {
      n = 0;
      anew = rtNaN;
      apnd = mtmp;
      n_too_large = false;
    } else if (muDoubleScalarIsInf(-varargin_2[k]) || muDoubleScalarIsInf(mtmp))
    {
      n = 0;
      anew = rtNaN;
      apnd = mtmp;
      n_too_large = true;
    } else {
      anew = -varargin_2[k];
      ndbl = muDoubleScalarFloor((mtmp - (-varargin_2[k])) + 0.5);
      apnd = -varargin_2[k] + ndbl;
      cdiff = apnd - mtmp;
      absa = muDoubleScalarAbs(-varargin_2[k]);
      absb = muDoubleScalarAbs(mtmp);
      if (muDoubleScalarAbs(cdiff) < 4.4408920985006262E-16 * muDoubleScalarMax
          (absa, absb)) {
        ndbl++;
        apnd = mtmp;
      } else if (cdiff > 0.0) {
        apnd = -varargin_2[k] + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      n_too_large = (2.147483647E+9 < ndbl);
      n = (int32_T)ndbl - 1;
    }

    f_st.site = &cc_emlrtRSI;
    if (!n_too_large) {
    } else {
      b_y = NULL;
      m9 = emlrtCreateCharArray(2, iv12);
      for (i = 0; i < 21; i++) {
        cv23[i] = cv24[i];
      }

      emlrtInitCharArrayR2013a(&f_st, 21, m9, cv23);
      emlrtAssign(&b_y, m9);
      g_st.site = &te_emlrtRSI;
      h_st.site = &cf_emlrtRSI;
      b_error(&g_st, b_message(&h_st, b_y, &l_emlrtMCI), &m_emlrtMCI);
    }

    i6 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n + 1;
    emxEnsureCapacity(&e_st, (emxArray__common *)y, i6, (int32_T)sizeof(real_T),
                      &j_emlrtRTEI);
    y->data[0] = anew;
    if (n + 1 > 1) {
      y->data[n] = apnd;
      i6 = n + (n < 0);
      if (i6 >= 0) {
        ixstart = (int32_T)((uint32_T)i6 >> 1);
      } else {
        ixstart = (int32_T)~(~(uint32_T)i6 >> 1);
      }

      f_st.site = &bc_emlrtRSI;
      for (ix = 1; ix < ixstart; ix++) {
        y->data[ix] = anew + (real_T)ix;
        y->data[n - ix] = apnd - (real_T)ix;
      }

      if (ixstart << 1 == n) {
        y->data[ixstart] = (anew + apnd) / 2.0;
      } else {
        y->data[ixstart] = anew + (real_T)ixstart;
        y->data[ixstart + 1] = apnd - (real_T)ixstart;
      }
    }

    b_mod(&b_st, y, 2.0 * (1200.0 + 400.0 * (real_T)k), r2);
    i6 = idxDir->size[0] * idxDir->size[1];
    idxDir->size[0] = 1;
    idxDir->size[1] = r2->size[1];
    emxEnsureCapacity(&b_st, (emxArray__common *)idxDir, i6, (int32_T)sizeof
                      (uint32_T), &k_emlrtRTEI);
    ixstart = r2->size[0] * r2->size[1];
    for (i6 = 0; i6 < ixstart; i6++) {
      mtmp = r2->data[i6] + 1.0;
      i7 = (int32_T)emlrtIntegerCheckFastR2012b(mtmp, &b_emlrtDCI, &b_st);
      idxDir->data[i6] = dimNums_data[emlrtDynamicBoundsCheckFastR2012b(i7, 1,
        dimNums_size_idx_1, &t_emlrtBCI, &b_st) - 1];
    }

    b_mod(&b_st, y, 2.0 * (1200.0 + 400.0 * (real_T)k), r2);
    sizeIdxDir[k] = r2->size[1];
    i6 = idxA->size[0];
    emlrtDynamicBoundsCheckFastR2012b(sizeIdxDir[k], 1, i6, &m_emlrtBCI, &b_st);
    ixstart = sizeIdxDir[k];
    i6 = r1->size[0];
    r1->size[0] = sizeIdxDir[k];
    emxEnsureCapacity(&b_st, (emxArray__common *)r1, i6, (int32_T)sizeof(int32_T),
                      &k_emlrtRTEI);
    for (i6 = 0; i6 < ixstart; i6++) {
      r1->data[i6] = i6;
    }

    b_mod(&b_st, y, 2.0 * (1200.0 + 400.0 * (real_T)k), r2);
    iv13[0] = r1->size[0];
    emlrtSubAssignSizeCheckR2012b(iv13, 1, *(int32_T (*)[2])r2->size, 2,
      &b_emlrtECI, &b_st);
    i6 = b_idxDir->size[0] * b_idxDir->size[1];
    b_idxDir->size[0] = 1;
    b_idxDir->size[1] = idxDir->size[1];
    emxEnsureCapacity(&b_st, (emxArray__common *)b_idxDir, i6, (int32_T)sizeof
                      (int32_T), &k_emlrtRTEI);
    ixstart = idxDir->size[1];
    for (i6 = 0; i6 < ixstart; i6++) {
      b_idxDir->data[b_idxDir->size[0] * i6] = (int32_T)idxDir->data
        [idxDir->size[0] * i6];
    }

    ixstart = r1->size[0];
    for (i6 = 0; i6 < ixstart; i6++) {
      idxA->data[r1->data[i6] + idxA->size[0] * k] = b_idxDir->data[i6];
    }

    sizeB[k] = (int32_T)((1200.0 + 400.0 * (real_T)k) + 2.0 * varargin_2[k]);
  }

  emxFree_int32_T(&b_idxDir);
  emxFree_real_T(&r2);
  emxFree_real_T(&y);
  emxFree_int32_T(&r1);
  emxFree_uint32_T(&idxDir);
  i6 = b->size[0] * b->size[1];
  b->size[0] = sizeB[0];
  b->size[1] = sizeB[1];
  emxEnsureCapacity(sp, (emxArray__common *)b, i6, (int32_T)sizeof(boolean_T),
                    &i_emlrtRTEI);
  for (ixstart = 1; ixstart - 1 < sizeB[1]; ixstart++) {
    i6 = b->size[0];
    for (i = 1; i - 1 < i6; i++) {
      i7 = b->size[0];
      ix = b->size[1];
      b_n = idxA->size[0];
      b_n = idxA->data[emlrtDynamicBoundsCheckFastR2012b(i, 1, b_n, &q_emlrtBCI,
        sp) - 1];
      n = idxA->size[0];
      n = idxA->data[(emlrtDynamicBoundsCheckFastR2012b(ixstart, 1, n,
        &s_emlrtBCI, sp) + idxA->size[0]) - 1];
      b->data[(emlrtDynamicBoundsCheckFastR2012b(i, 1, i7, &n_emlrtBCI, sp) +
               b->size[0] * (emlrtDynamicBoundsCheckFastR2012b(ixstart, 1, ix,
                 &o_emlrtBCI, sp) - 1)) - 1] = varargin_1
        [(emlrtDynamicBoundsCheckFastR2012b(b_n, 1, 1200, &p_emlrtBCI, sp) +
          1200 * (emlrtDynamicBoundsCheckFastR2012b(n, 1, 1600, &r_emlrtBCI, sp)
                  - 1)) - 1];
    }
  }

  emxFree_int32_T(&idxA);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (padarray.c) */
