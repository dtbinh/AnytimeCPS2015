/*
 * run_perception_module_for_srcgen.c
 *
 * Code generation for function 'run_perception_module_for_srcgen'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "posteriors_for_srcgen.h"
#include "region_properties_for_srcgen.h"
#include "eml_int_forloop_overflow_check.h"
#include "label_connected_components_for_srcgen.h"
#include "medfilt2.h"
#include "sum.h"
#include "repmat.h"
#include "error.h"
#include "any.h"
#include "rdivide.h"
#include "run_perception_module_for_srcgen_mexutil.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = { 11, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRSInfo b_emlrtRSI = { 16, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRSInfo c_emlrtRSI = { 17, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRSInfo d_emlrtRSI = { 30, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRSInfo e_emlrtRSI = { 31, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRSInfo f_emlrtRSI = { 41, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRSInfo g_emlrtRSI = { 42, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRSInfo h_emlrtRSI = { 45, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRSInfo i_emlrtRSI = { 56, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRSInfo j_emlrtRSI = { 61, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRSInfo k_emlrtRSI = { 10, "preprocess_img",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\preprocess_img.m"
};

static emlrtRSInfo l_emlrtRSI = { 12, "preprocess_img",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\preprocess_img.m"
};

static emlrtRSInfo m_emlrtRSI = { 13, "preprocess_img",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\preprocess_img.m"
};

static emlrtRSInfo ib_emlrtRSI = { 122, "imerode",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\imerode.m" };

static emlrtRSInfo jb_emlrtRSI = { 17, "morphop",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\+images\\+internal\\morphop.m"
};

static emlrtRSInfo kb_emlrtRSI = { 19, "morphop",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\+images\\+internal\\+coder\\morphop.m"
};

static emlrtRSInfo lb_emlrtRSI = { 374, "morphop",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\+images\\+internal\\+coder\\morphop.m"
};

static emlrtRSInfo mb_emlrtRSI = { 517, "morphop",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\+images\\+internal\\+coder\\morphop.m"
};

static emlrtRSInfo ke_emlrtRSI = { 11, "eml_li_find",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_li_find.m"
};

static emlrtRSInfo le_emlrtRSI = { 26, "eml_li_find",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_li_find.m"
};

static emlrtRSInfo me_emlrtRSI = { 39, "eml_li_find",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_li_find.m"
};

static emlrtMCInfo emlrtMCI = { 14, 5, "eml_li_find",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_li_find.m"
};

static emlrtRTEInfo emlrtRTEI = { 1, 10, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRTEInfo b_emlrtRTEI = { 20, 9, "eml_li_find",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_li_find.m"
};

static emlrtRTEInfo c_emlrtRTEI = { 52, 5, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRTEInfo d_emlrtRTEI = { 56, 5, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRTEInfo e_emlrtRTEI = { 43, 1, "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m"
};

static emlrtRTEInfo f_emlrtRTEI = { 6, 1, "svmpredict_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\svmpredict_for_srcgen.m"
};

static emlrtDCInfo emlrtDCI = { 20, 34, "eml_li_find",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_li_find.m",
  4 };

static emlrtBCInfo emlrtBCI = { -1, -1, 11, 50, "SupportVectors",
  "svmpredict_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\svmpredict_for_srcgen.m",
  0 };

static emlrtBCInfo b_emlrtBCI = { -1, -1, 8, 18, "features",
  "svmpredict_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\svmpredict_for_srcgen.m",
  0 };

static emlrtECInfo emlrtECI = { 2, 6, 23, "svmpredict_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\svmpredict_for_srcgen.m"
};

static emlrtBCInfo c_emlrtBCI = { -1, -1, 54, 26, "featuresPosClass",
  "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m",
  0 };

static emlrtBCInfo d_emlrtBCI = { -1, -1, 54, 67, "statsPosClass",
  "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m",
  0 };

static emlrtBCInfo e_emlrtBCI = { -1, -1, 54, 48, "statsPosClass",
  "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m",
  0 };

static emlrtBCInfo f_emlrtBCI = { 1, 3, 12, 11, "I",
  "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m",
  0 };

static emlrtBCInfo g_emlrtBCI = { -1, -1, 61, 33, "statsPosClass",
  "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m",
  0 };

static emlrtBCInfo h_emlrtBCI = { -1, -1, 14, 5, "label",
  "svmpredict_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\svmpredict_for_srcgen.m",
  0 };

static emlrtBCInfo i_emlrtBCI = { -1, -1, 11, 17, "w", "svmpredict_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\svmpredict_for_srcgen.m",
  0 };

static emlrtBCInfo j_emlrtBCI = { -1, -1, 54, 87, "statsPosClass",
  "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m",
  0 };

static emlrtBCInfo k_emlrtBCI = { -1, -1, 54, 107, "statsPosClass",
  "run_perception_module_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\run_perception_module_for_srcgen.m",
  0 };

static emlrtRSInfo we_emlrtRSI = { 14, "eml_li_find",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_li_find.m"
};

/* Function Declarations */
static int32_T compute_nones(const boolean_T x[1920000]);
static void eml_li_find(const emlrtStack *sp, const boolean_T x[1920000],
  emxArray_int32_T *y);

/* Function Definitions */
static int32_T compute_nones(const boolean_T x[1920000])
{
  int32_T k;
  int32_T i;
  k = 0;
  for (i = 0; i < 1920000; i++) {
    if (x[i]) {
      k++;
    }
  }

  return k;
}

static void eml_li_find(const emlrtStack *sp, const boolean_T x[1920000],
  emxArray_int32_T *y)
{
  int32_T k;
  const mxArray *b_y;
  const mxArray *m1;
  int32_T i;
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  k = compute_nones(x);
  if (k <= 1920000) {
  } else {
    b_y = NULL;
    m1 = emlrtCreateString("Assertion failed.");
    emlrtAssign(&b_y, m1);
    st.site = &we_emlrtRSI;
    b_error(&st, b_y, &emlrtMCI);
  }

  emlrtNonNegativeCheckFastR2012b(k, &emlrtDCI, sp);
  i = y->size[0];
  y->size[0] = k;
  emxEnsureCapacity(sp, (emxArray__common *)y, i, (int32_T)sizeof(int32_T),
                    &b_emlrtRTEI);
  k = 0;
  for (i = 0; i < 1920000; i++) {
    if (x[i]) {
      y->data[k] = i + 1;
      k++;
    }
  }
}

void run_perception_module_for_srcgen(c_run_perception_module_for_src *SD, const
  emlrtStack *sp, const uint8_T Im[5760000], const uint8_T colors[3], real_T
  minAcceptanceProbScalingFactor, real_T minSignificanceProb, real_T
  minAcceptanceProb, const real_T muPOI[12], const real_T SigmaPOI[36], const
  real_T ComponentProportionPOI[4], const real_T muNON[12], const real_T
  SigmaNON[36], const real_T ComponentProportionNON[4], const emxArray_real_T
  *Alpha, const emxArray_real_T *SupportVectorLabels, real_T KernelScale, const
  emxArray_real_T *SupportVectors, real_T Bias)
{
  int32_T i0;
  emxArray_int32_T *r0;
  int32_T ix;
  real_T y;
  boolean_T bv0[1200];
  int32_T i1;
  int32_T k;
  int32_T exitg2;
  int32_T n;
  boolean_T overflow;
  real_T asize[2];
  real_T nsize[2];
  int32_T i;
  boolean_T b_ix;
  boolean_T exitg1;
  boolean_T b_k;
  emxArray_creal_T *statsPosClass;
  emxArray_creal_T *featuresPosClass;
  real_T statsPosClass_re;
  real_T statsPosClass_im;
  real_T scale;
  real_T absxk;
  real_T t;
  real_T s;
  emxArray_real_T *label;
  int32_T b_Alpha[2];
  int32_T b_SupportVectorLabels[2];
  emxArray_real_T *w;
  creal_T b_y[3];
  emxArray_boolean_T *x;
  const mxArray *c_y;
  const mxArray *m0;
  emxArray_int32_T *d_y;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
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
  emlrtHeapReferenceStackEnterFcnR2012b(sp);

  /*  Detect pix of interest */
  minAcceptanceProb /= minAcceptanceProbScalingFactor;

  /*  allow for 1st iteration of while loop */
  st.site = &emlrtRSI;
  for (i0 = 0; i0 < 5760000; i0++) {
    /*  Remove the NaNs to avoid weirdness when computing probabilities  */
    SD->f3.I[i0] = Im[i0];
  }

  /*  Normalize */
  sum(SD->f3.I, SD->f3.s);
  for (i0 = 0; i0 < 1920000; i0++) {
    SD->f3.B[i0] = (SD->f3.s[i0] == 0.0);
    SD->f3.b_s[i0] = (SD->f3.s[i0] == 0.0);
  }

  repmat(SD->f3.B, SD->f3.S);
  emxInit_int32_T(&st, &r0, 1, &emlrtRTEI, true);
  b_st.site = &k_emlrtRSI;
  eml_li_find(&b_st, SD->f3.b_s, r0);
  ix = r0->size[0];
  for (i0 = 0; i0 < ix; i0++) {
    SD->f3.s[r0->data[i0] - 1] = 1.0;
  }

  emxFree_int32_T(&r0);
  b_repmat(SD->f3.s, SD->f3.dv0);
  rdivide(SD->f3.I, SD->f3.dv0, SD->f3.dv1);
  for (i0 = 0; i0 < 5760000; i0++) {
    y = (real_T)SD->f3.S[i0] * SD->f3.I[i0] + (real_T)!SD->f3.S[i0] * SD->
      f3.dv1[i0];
    SD->f3.S[i0] = muDoubleScalarIsNaN(y);
    SD->f3.I[i0] = y;
  }

  b_st.site = &l_emlrtRSI;
  any(&b_st, SD->f3.S, SD->f3.M);
  b_st.site = &l_emlrtRSI;
  b_any(&b_st, SD->f3.M, bv0);
  if (c_any(bv0)) {
    b_st.site = &m_emlrtRSI;
    error(&b_st);
  }

  for (i0 = 0; i0 < 3; i0++) {
    for (i1 = 0; i1 < 1600; i1++) {
      for (k = 0; k < 1200; k++) {
        ix = colors[i0];
        SD->f3.b_I[(k + 1200 * i1) + 1920000 * i0] = SD->f3.I[(k + 1200 * i1) +
          1920000 * (emlrtDynamicBoundsCheckFastR2012b(ix, 1, 3, &f_emlrtBCI, sp)
                     - 1)];
      }
    }
  }

  for (i0 = 0; i0 < 3; i0++) {
    for (i1 = 0; i1 < 1600; i1++) {
      memcpy(&SD->f3.I[1200 * i1 + 1920000 * i0], &SD->f3.b_I[1200 * i1 +
             1920000 * i0], 1200U * sizeof(real_T));
    }
  }

  memcpy(&SD->f3.candidate[0], &SD->f3.I[0], 5760000U * sizeof(real_T));
  st.site = &b_emlrtRSI;
  posteriors_for_srcgen(SD, &st, muPOI, SigmaPOI, ComponentProportionPOI,
                        SD->f3.candidate, SD->f3.posteriorspoi);
  st.site = &c_emlrtRSI;
  posteriors_for_srcgen(SD, &st, muNON, SigmaNON, ComponentProportionNON,
                        SD->f3.candidate, SD->f3.posteriorsnon);

  /*  For each pix, decide if it's best described by poi or non */
  c_repmat(ComponentProportionPOI, SD->f3.dv2);
  for (i0 = 0; i0 < 7680000; i0++) {
    SD->f3.b_posteriorspoi[i0] = SD->f3.posteriorspoi[i0] * SD->f3.dv2[i0];
  }

  b_sum(SD->f3.b_posteriorspoi, SD->f3.s);
  c_repmat(ComponentProportionNON, SD->f3.dv2);
  for (i0 = 0; i0 < 7680000; i0++) {
    SD->f3.posteriorspoi[i0] = SD->f3.posteriorsnon[i0] * SD->f3.dv2[i0];
  }

  b_sum(SD->f3.posteriorspoi, SD->f3.d2);
  memset(&SD->f3.clusterObjOfInterest[0], 0, 1920000U * sizeof(boolean_T));

  /* initialize while */
  do {
    exitg2 = 0;
    n = 0;
    for (k = 0; k < 1920000; k++) {
      if (SD->f3.clusterObjOfInterest[k]) {
        n++;
      }
    }

    if ((n == 0) && (minAcceptanceProb >= minSignificanceProb)) {
      minAcceptanceProb *= minAcceptanceProbScalingFactor;
      for (k = 0; k < 1920000; k++) {
        SD->f3.clusterObjOfInterest[k] = (SD->f3.s[k] > muDoubleScalarMax
          (SD->f3.d2[k], minAcceptanceProb));
      }

      emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, sp);
    } else {
      exitg2 = 1;
    }
  } while (exitg2 == 0);

  /*  Filter out the smaller things */
  memcpy(&SD->f3.M[0], &SD->f3.clusterObjOfInterest[0], 1920000U * sizeof
         (boolean_T));
  st.site = &d_emlrtRSI;
  st.site = &d_emlrtRSI;
  b_st.site = &ib_emlrtRSI;
  c_st.site = &jb_emlrtRSI;
  d_st.site = &kb_emlrtRSI;
  d_st.site = &lb_emlrtRSI;
  e_st.site = &mb_emlrtRSI;
  overflow = true;
  for (i0 = 0; i0 < 2; i0++) {
    asize[i0] = 1200.0 + 400.0 * (real_T)i0;
    nsize[i0] = 1.0;
  }

  erode_binary_twod_tbb(SD->f3.M, asize, 2.0, &overflow, nsize, 2.0, SD->f3.B);
  st.site = &e_emlrtRSI;
  medfilt2(&st, SD->f3.B, SD->f3.M);

  /*  Connect components and extract features for the positive class, i.e. of barrel objects. */
  /*  */
  /*  stats = regionprops(M, 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity', 'Centroid'); */
  /*  statsPosClass = zeros(length(stats),6); */
  /*  for i=1:length(stats) */
  /*      statsPosClass(i,:) = [stats(i).MajorAxisLength, stats(i).MinorAxisLength, stats(i).Eccentricity, stats(i).Solidity, stats(i).Centroid]; */
  /*  end     */
  /*  % M = [1 1 1 0 0 0;1 0 0 1 1 1;1 1 0 0 0 0 ; 1 1 0 0 0 0;1 1 0 0 0 1;0 0 0 0 0 1]; */
  st.site = &f_emlrtRSI;
  c_label_connected_components_fo(&st, SD->f3.M, SD->f3.s);
  st.site = &g_emlrtRSI;
  b_st.site = &fc_emlrtRSI;
  c_st.site = &gc_emlrtRSI;
  ix = 0;
  for (i = 0; i < 1600; i++) {
    ix += 1200;
    d_st.site = &hc_emlrtRSI;
    k = ix - 1199;
    if (muDoubleScalarIsNaN(SD->f3.s[ix - 1200])) {
      e_st.site = &jc_emlrtRSI;
      if (ix - 1198 > ix) {
        b_ix = false;
      } else {
        b_ix = (ix > 2147483646);
      }

      if (b_ix) {
        f_st.site = &p_emlrtRSI;
        check_forloop_overflow_error(&f_st);
      }

      n = ix - 1198;
      exitg1 = false;
      while ((!exitg1) && (n <= ix)) {
        k = n;
        if (!muDoubleScalarIsNaN(SD->f3.s[n - 1])) {
          exitg1 = true;
        } else {
          n++;
        }
      }
    }

    if (k < ix) {
      e_st.site = &ic_emlrtRSI;
      if (k + 1 > ix) {
        b_k = false;
      } else {
        b_k = (ix > 2147483646);
      }

      if (b_k) {
        f_st.site = &p_emlrtRSI;
        check_forloop_overflow_error(&f_st);
      }
    }
  }

  emxInit_creal_T(&c_st, &statsPosClass, 2, &e_emlrtRTEI, true);

  /*  Keep it simple - properties are hard-coded in function */
  st.site = &h_emlrtRSI;
  region_properties_for_srcgen(SD, &st, SD->f3.s, statsPosClass);
  if (0 == statsPosClass->size[0]) {
    n = 0;
  } else {
    n = muIntScalarMax_sint32(statsPosClass->size[0], 6);
  }

  /*  Detect shapes */
  if (!(statsPosClass->size[0] == 0)) {
    emxInit_creal_T(sp, &featuresPosClass, 2, &c_emlrtRTEI, true);

    /*  Vector = major, minor, ecc, solidity */
    i0 = featuresPosClass->size[0] * featuresPosClass->size[1];
    featuresPosClass->size[0] = n;
    featuresPosClass->size[1] = 3;
    emxEnsureCapacity(sp, (emxArray__common *)featuresPosClass, i0, (int32_T)
                      sizeof(creal_T), &emlrtRTEI);
    ix = n * 3;
    for (i0 = 0; i0 < ix; i0++) {
      featuresPosClass->data[i0].re = 0.0;
      featuresPosClass->data[i0].im = 0.0;
    }

    i = 0;
    while (i <= n - 1) {
      i0 = statsPosClass->size[0];
      i1 = i + 1;
      emlrtDynamicBoundsCheckFastR2012b(i1, 1, i0, &e_emlrtBCI, sp);
      i0 = statsPosClass->size[0];
      i1 = i + 1;
      emlrtDynamicBoundsCheckFastR2012b(i1, 1, i0, &d_emlrtBCI, sp);
      ix = featuresPosClass->size[0];
      i0 = 1 + i;
      emlrtDynamicBoundsCheckFastR2012b(i0, 1, ix, &c_emlrtBCI, sp);
      statsPosClass_re = statsPosClass->data[i].re;
      statsPosClass_im = statsPosClass->data[i].im;
      scale = statsPosClass->data[i + statsPosClass->size[0]].re;
      absxk = statsPosClass->data[i + statsPosClass->size[0]].im;
      if (absxk == 0.0) {
        if (statsPosClass_im == 0.0) {
          featuresPosClass->data[i].re = statsPosClass_re / scale;
          featuresPosClass->data[i].im = 0.0;
        } else if (statsPosClass_re == 0.0) {
          featuresPosClass->data[i].re = 0.0;
          featuresPosClass->data[i].im = statsPosClass_im / scale;
        } else {
          featuresPosClass->data[i].re = statsPosClass_re / scale;
          featuresPosClass->data[i].im = statsPosClass_im / scale;
        }
      } else if (scale == 0.0) {
        if (statsPosClass_re == 0.0) {
          featuresPosClass->data[i].re = statsPosClass_im / absxk;
          featuresPosClass->data[i].im = 0.0;
        } else if (statsPosClass_im == 0.0) {
          featuresPosClass->data[i].re = 0.0;
          featuresPosClass->data[i].im = -(statsPosClass_re / absxk);
        } else {
          featuresPosClass->data[i].re = statsPosClass_im / absxk;
          featuresPosClass->data[i].im = -(statsPosClass_re / absxk);
        }
      } else {
        t = muDoubleScalarAbs(scale);
        y = muDoubleScalarAbs(absxk);
        if (t > y) {
          s = absxk / scale;
          y = scale + s * absxk;
          featuresPosClass->data[i].re = (statsPosClass_re + s *
            statsPosClass_im) / y;
          featuresPosClass->data[i].im = (statsPosClass_im - s *
            statsPosClass_re) / y;
        } else if (y == t) {
          if (scale > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }

          if (absxk > 0.0) {
            y = 0.5;
          } else {
            y = -0.5;
          }

          featuresPosClass->data[i].re = (statsPosClass_re * scale +
            statsPosClass_im * y) / t;
          featuresPosClass->data[i].im = (statsPosClass_im * scale -
            statsPosClass_re * y) / t;
        } else {
          s = scale / absxk;
          y = absxk + s * scale;
          featuresPosClass->data[i].re = (s * statsPosClass_re +
            statsPosClass_im) / y;
          featuresPosClass->data[i].im = (s * statsPosClass_im -
            statsPosClass_re) / y;
        }
      }

      i0 = statsPosClass->size[0];
      i1 = 1 + i;
      featuresPosClass->data[i + featuresPosClass->size[0]].re =
        statsPosClass->data[(emlrtDynamicBoundsCheckFastR2012b(i1, 1, i0,
        &j_emlrtBCI, sp) + (statsPosClass->size[0] << 1)) - 1].re;
      i0 = statsPosClass->size[0];
      i1 = 1 + i;
      featuresPosClass->data[i + featuresPosClass->size[0]].im =
        statsPosClass->data[(emlrtDynamicBoundsCheckFastR2012b(i1, 1, i0,
        &j_emlrtBCI, sp) + (statsPosClass->size[0] << 1)) - 1].im;
      i0 = statsPosClass->size[0];
      i1 = 1 + i;
      featuresPosClass->data[i + (featuresPosClass->size[0] << 1)].re =
        statsPosClass->data[(emlrtDynamicBoundsCheckFastR2012b(i1, 1, i0,
        &k_emlrtBCI, sp) + statsPosClass->size[0] * 3) - 1].re;
      i0 = statsPosClass->size[0];
      i1 = 1 + i;
      featuresPosClass->data[i + (featuresPosClass->size[0] << 1)].im =
        statsPosClass->data[(emlrtDynamicBoundsCheckFastR2012b(i1, 1, i0,
        &k_emlrtBCI, sp) + statsPosClass->size[0] * 3) - 1].im;
      i++;
      emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, sp);
    }

    emxInit_real_T(sp, &label, 1, &d_emlrtRTEI, true);
    st.site = &i_emlrtRSI;

    /*  labelAuto = predict(SVMModel, featuresPosClass); */
    i0 = label->size[0];
    label->size[0] = featuresPosClass->size[0];
    emxEnsureCapacity(&st, (emxArray__common *)label, i0, (int32_T)sizeof(real_T),
                      &emlrtRTEI);
    ix = featuresPosClass->size[0];
    for (i0 = 0; i0 < ix; i0++) {
      label->data[i0] = 0.0;
    }

    for (i0 = 0; i0 < 2; i0++) {
      b_Alpha[i0] = Alpha->size[i0];
    }

    for (i0 = 0; i0 < 2; i0++) {
      b_SupportVectorLabels[i0] = SupportVectorLabels->size[i0];
    }

    b_emxInit_real_T(&st, &w, 2, &f_emlrtRTEI, true);
    emlrtSizeEqCheck2DFastR2012b(b_Alpha, b_SupportVectorLabels, &emlrtECI, &st);
    i0 = w->size[0] * w->size[1];
    w->size[0] = 1;
    w->size[1] = Alpha->size[1];
    emxEnsureCapacity(&st, (emxArray__common *)w, i0, (int32_T)sizeof(real_T),
                      &emlrtRTEI);
    ix = Alpha->size[0] * Alpha->size[1];
    for (i0 = 0; i0 < ix; i0++) {
      w->data[i0] = Alpha->data[i0] * SupportVectorLabels->data[i0];
    }

    k = 0;
    while (k <= featuresPosClass->size[0] - 1) {
      i0 = featuresPosClass->size[0];
      i1 = k + 1;
      emlrtDynamicBoundsCheckFastR2012b(i1, 1, i0, &b_emlrtBCI, &st);
      s = 0.0;
      i = 0;
      while (i <= Alpha->size[1] - 1) {
        i0 = SupportVectors->size[0];
        i1 = i + 1;
        emlrtDynamicBoundsCheckFastR2012b(i1, 1, i0, &emlrtBCI, &st);
        for (i0 = 0; i0 < 3; i0++) {
          y = SupportVectors->data[i + SupportVectors->size[0] * i0] -
            featuresPosClass->data[k + featuresPosClass->size[0] * i0].re;
          scale = 0.0 - featuresPosClass->data[k + featuresPosClass->size[0] *
            i0].im;
          if (scale == 0.0) {
            b_y[i0].re = y / KernelScale;
            b_y[i0].im = 0.0;
          } else if (y == 0.0) {
            b_y[i0].re = 0.0;
            b_y[i0].im = scale / KernelScale;
          } else {
            b_y[i0].re = y / KernelScale;
            b_y[i0].im = scale / KernelScale;
          }
        }

        y = 0.0;
        scale = 2.2250738585072014E-308;
        for (ix = 0; ix < 3; ix++) {
          absxk = muDoubleScalarAbs(b_y[ix].re);
          if (absxk > scale) {
            t = scale / absxk;
            y = 1.0 + y * t * t;
            scale = absxk;
          } else {
            t = absxk / scale;
            y += t * t;
          }

          absxk = muDoubleScalarAbs(b_y[ix].im);
          if (absxk > scale) {
            t = scale / absxk;
            y = 1.0 + y * t * t;
            scale = absxk;
          } else {
            t = absxk / scale;
            y += t * t;
          }
        }

        y = scale * muDoubleScalarSqrt(y);
        i0 = w->size[1];
        i1 = 1 + i;
        s += w->data[emlrtDynamicBoundsCheckFastR2012b(i1, 1, i0, &i_emlrtBCI,
          &st) - 1] * muDoubleScalarExp(-(y * y));
        i++;
        emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, &st);
      }

      s += Bias;
      i0 = label->size[0];
      i1 = 1 + k;
      label->data[emlrtDynamicBoundsCheckFastR2012b(i1, 1, i0, &h_emlrtBCI, &st)
        - 1] = muDoubleScalarSign(s);
      k++;
      emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, &st);
    }

    emxFree_real_T(&w);
    emxFree_creal_T(&featuresPosClass);
    emxInit_boolean_T(&st, &x, 1, &emlrtRTEI, true);

    /*  Discard low-scoring objects */
    /*  ..?? */
    st.site = &j_emlrtRSI;
    i0 = x->size[0];
    x->size[0] = label->size[0];
    emxEnsureCapacity(&st, (emxArray__common *)x, i0, (int32_T)sizeof(boolean_T),
                      &emlrtRTEI);
    ix = label->size[0];
    for (i0 = 0; i0 < ix; i0++) {
      x->data[i0] = (label->data[i0] == 1.0);
    }

    emxFree_real_T(&label);
    n = x->size[0];
    b_st.site = &ke_emlrtRSI;
    k = 0;
    c_st.site = &me_emlrtRSI;
    if (1 > x->size[0]) {
      overflow = false;
    } else {
      overflow = (x->size[0] > 2147483646);
    }

    if (overflow) {
      d_st.site = &p_emlrtRSI;
      check_forloop_overflow_error(&d_st);
    }

    for (i = 1; i <= n; i++) {
      if (x->data[i - 1]) {
        k++;
      }
    }

    if (k <= x->size[0]) {
    } else {
      c_y = NULL;
      m0 = emlrtCreateString("Assertion failed.");
      emlrtAssign(&c_y, m0);
      b_st.site = &we_emlrtRSI;
      b_error(&b_st, c_y, &emlrtMCI);
    }

    emxInit_int32_T(&st, &d_y, 1, &emlrtRTEI, true);
    emlrtNonNegativeCheckFastR2012b(k, &emlrtDCI, &st);
    i0 = d_y->size[0];
    d_y->size[0] = k;
    emxEnsureCapacity(&st, (emxArray__common *)d_y, i0, (int32_T)sizeof(int32_T),
                      &b_emlrtRTEI);
    ix = 0;
    b_st.site = &le_emlrtRSI;
    if (1 > x->size[0]) {
      overflow = false;
    } else {
      overflow = (x->size[0] > 2147483646);
    }

    if (overflow) {
      c_st.site = &p_emlrtRSI;
      check_forloop_overflow_error(&c_st);
    }

    for (i = 1; i <= n; i++) {
      if (x->data[i - 1]) {
        d_y->data[ix] = i;
        ix++;
      }
    }

    emxFree_boolean_T(&x);
    ix = d_y->size[0];
    for (i0 = 0; i0 < ix; i0++) {
      i1 = statsPosClass->size[0];
      k = d_y->data[i0];
      emlrtDynamicBoundsCheckFastR2012b(k, 1, i1, &g_emlrtBCI, sp);
    }

    emxFree_int32_T(&d_y);

    /*  1 is the positive class index */
    /*                  figure */
    /*                  imshow(Im(:,:,1)); */
    /*                  hold on */
    /*                  centroids = cat(1, selectedObj(:,5:6)); */
    /*                  plot(centroids(:,1), centroids(:,2), 'b*') */
  }

  emxFree_creal_T(&statsPosClass);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (run_perception_module_for_srcgen.c) */
