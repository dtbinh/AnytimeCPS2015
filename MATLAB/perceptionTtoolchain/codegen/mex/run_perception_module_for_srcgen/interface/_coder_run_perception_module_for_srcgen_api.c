/*
 * _coder_run_perception_module_for_srcgen_api.c
 *
 * Code generation for function '_coder_run_perception_module_for_srcgen_api'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "_coder_run_perception_module_for_srcgen_api.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRTEInfo bb_emlrtRTEI = { 1, 1,
  "_coder_run_perception_module_for_srcgen_api", "" };

/* Function Declarations */
static void ab_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void bb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static uint8_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Im,
  const char_T *identifier))[5760000];
static uint8_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[5760000];
static uint8_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *colors,
  const char_T *identifier))[3];
static uint8_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3];
static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *minAcceptanceProbScalingFactor, const char_T *identifier);
static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *muPOI,
  const char_T *identifier))[12];
static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[12];
static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *SigmaPOI,
  const char_T *identifier))[36];
static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[36];
static real_T (*m_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *ComponentProportionPOI, const char_T *identifier))[4];
static real_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[4];
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Alpha, const
  char_T *identifier, emxArray_real_T *y);
static void p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *SupportVectors, const char_T *identifier, emxArray_real_T *y);
static void r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static uint8_T (*t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[5760000];
static uint8_T (*u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static real_T v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T (*w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[12];
static real_T (*x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[36];
static real_T (*y_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4];

/* Function Definitions */
static void ab_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  int32_T iv29[2];
  boolean_T bv1[2];
  int32_T i15;
  static const boolean_T bv2[2] = { false, true };

  int32_T iv30[2];
  for (i15 = 0; i15 < 2; i15++) {
    iv29[i15] = 1 + -2 * i15;
    bv1[i15] = bv2[i15];
  }

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv29, bv1, iv30);
  ret->size[0] = iv30[0];
  ret->size[1] = iv30[1];
  ret->allocatedSize = ret->size[0] * ret->size[1];
  ret->data = (real_T *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void bb_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  int32_T iv31[2];
  boolean_T bv3[2];
  int32_T i16;
  static const boolean_T bv4[2] = { true, false };

  int32_T iv32[2];
  for (i16 = 0; i16 < 2; i16++) {
    iv31[i16] = (i16 << 2) - 1;
    bv3[i16] = bv4[i16];
  }

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv31, bv3, iv32);
  ret->size[0] = iv32[0];
  ret->size[1] = iv32[1];
  ret->allocatedSize = ret->size[0] * ret->size[1];
  ret->data = (real_T *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static uint8_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Im,
  const char_T *identifier))[5760000]
{
  uint8_T (*y)[5760000];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = d_emlrt_marshallIn(sp, emlrtAlias(Im), &thisId);
  emlrtDestroyArray(&Im);
  return y;
}
  static uint8_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[5760000]
{
  uint8_T (*y)[5760000];
  y = t_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static uint8_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *colors,
  const char_T *identifier))[3]
{
  uint8_T (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = f_emlrt_marshallIn(sp, emlrtAlias(colors), &thisId);
  emlrtDestroyArray(&colors);
  return y;
}
  static uint8_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3]
{
  uint8_T (*y)[3];
  y = u_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *minAcceptanceProbScalingFactor, const char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = h_emlrt_marshallIn(sp, emlrtAlias(minAcceptanceProbScalingFactor), &thisId);
  emlrtDestroyArray(&minAcceptanceProbScalingFactor);
  return y;
}

static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = v_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *muPOI,
  const char_T *identifier))[12]
{
  real_T (*y)[12];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = j_emlrt_marshallIn(sp, emlrtAlias(muPOI), &thisId);
  emlrtDestroyArray(&muPOI);
  return y;
}
  static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[12]
{
  real_T (*y)[12];
  y = w_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *SigmaPOI,
  const char_T *identifier))[36]
{
  real_T (*y)[36];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = l_emlrt_marshallIn(sp, emlrtAlias(SigmaPOI), &thisId);
  emlrtDestroyArray(&SigmaPOI);
  return y;
}
  static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[36]
{
  real_T (*y)[36];
  y = x_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*m_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *ComponentProportionPOI, const char_T *identifier))[4]
{
  real_T (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = n_emlrt_marshallIn(sp, emlrtAlias(ComponentProportionPOI), &thisId);
  emlrtDestroyArray(&ComponentProportionPOI);
  return y;
}
  static real_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[4]
{
  real_T (*y)[4];
  y = y_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Alpha, const
  char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  p_emlrt_marshallIn(sp, emlrtAlias(Alpha), &thisId, y);
  emlrtDestroyArray(&Alpha);
}

static void p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  ab_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void q_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *SupportVectors, const char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  r_emlrt_marshallIn(sp, emlrtAlias(SupportVectors), &thisId, y);
  emlrtDestroyArray(&SupportVectors);
}

static void r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  bb_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static uint8_T (*t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[5760000]
{
  uint8_T (*ret)[5760000];
  int32_T iv22[3];
  int32_T i;
  static const int16_T iv23[3] = { 1200, 1600, 3 };

  for (i = 0; i < 3; i++) {
    iv22[i] = iv23[i];
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "uint8", false, 3U, iv22);
  ret = (uint8_T (*)[5760000])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static uint8_T (*u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3]
{
  uint8_T (*ret)[3];
  int32_T iv24[2];
  int32_T i12;
  for (i12 = 0; i12 < 2; i12++) {
    iv24[i12] = 1 + (i12 << 1);
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "uint8", false, 2U, iv24);
  ret = (uint8_T (*)[3])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, 0);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[12]
{
  real_T (*ret)[12];
  int32_T iv25[2];
  int32_T i13;
  for (i13 = 0; i13 < 2; i13++) {
    iv25[i13] = 4 - i13;
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv25);
  ret = (real_T (*)[12])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static real_T (*x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[36]
{
  real_T (*ret)[36];
  int32_T iv26[3];
  int32_T i;
  static const int8_T iv27[3] = { 3, 3, 4 };

  for (i = 0; i < 3; i++) {
    iv26[i] = iv27[i];
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 3U, iv26);
  ret = (real_T (*)[36])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*y_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4]
{
  real_T (*ret)[4];
  int32_T iv28[2];
  int32_T i14;
  for (i14 = 0; i14 < 2; i14++) {
    iv28[i14] = 1 + 3 * i14;
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv28);
  ret = (real_T (*)[4])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  void run_perception_module_for_srcgen_api(c_run_perception_module_for_src *SD,
  const mxArray * const prhs[16])
{
  emxArray_real_T *Alpha;
  emxArray_real_T *SupportVectorLabels;
  emxArray_real_T *SupportVectors;
  uint8_T (*Im)[5760000];
  uint8_T (*colors)[3];
  real_T minAcceptanceProbScalingFactor;
  real_T minSignificanceProb;
  real_T minAcceptanceProb;
  real_T (*muPOI)[12];
  real_T (*SigmaPOI)[36];
  real_T (*ComponentProportionPOI)[4];
  real_T (*muNON)[12];
  real_T (*SigmaNON)[36];
  real_T (*ComponentProportionNON)[4];
  real_T KernelScale;
  real_T Bias;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  b_emxInit_real_T(&st, &Alpha, 2, &bb_emlrtRTEI, true);
  b_emxInit_real_T(&st, &SupportVectorLabels, 2, &bb_emlrtRTEI, true);
  b_emxInit_real_T(&st, &SupportVectors, 2, &bb_emlrtRTEI, true);

  /* Marshall function inputs */
  Im = c_emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "Im");
  colors = e_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "colors");
  minAcceptanceProbScalingFactor = g_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]),
    "minAcceptanceProbScalingFactor");
  minSignificanceProb = g_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]),
    "minSignificanceProb");
  minAcceptanceProb = g_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]),
    "minAcceptanceProb");
  muPOI = i_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "muPOI");
  SigmaPOI = k_emlrt_marshallIn(&st, emlrtAlias(prhs[6]), "SigmaPOI");
  ComponentProportionPOI = m_emlrt_marshallIn(&st, emlrtAlias(prhs[7]),
    "ComponentProportionPOI");
  muNON = i_emlrt_marshallIn(&st, emlrtAlias(prhs[8]), "muNON");
  SigmaNON = k_emlrt_marshallIn(&st, emlrtAlias(prhs[9]), "SigmaNON");
  ComponentProportionNON = m_emlrt_marshallIn(&st, emlrtAlias(prhs[10]),
    "ComponentProportionNON");
  o_emlrt_marshallIn(&st, emlrtAlias(prhs[11]), "Alpha", Alpha);
  o_emlrt_marshallIn(&st, emlrtAlias(prhs[12]), "SupportVectorLabels",
                     SupportVectorLabels);
  KernelScale = g_emlrt_marshallIn(&st, emlrtAliasP(prhs[13]), "KernelScale");
  q_emlrt_marshallIn(&st, emlrtAlias(prhs[14]), "SupportVectors", SupportVectors);
  Bias = g_emlrt_marshallIn(&st, emlrtAliasP(prhs[15]), "Bias");

  /* Invoke the target function */
  run_perception_module_for_srcgen(SD, &st, *Im, *colors,
    minAcceptanceProbScalingFactor, minSignificanceProb, minAcceptanceProb,
    *muPOI, *SigmaPOI, *ComponentProportionPOI, *muNON, *SigmaNON,
    *ComponentProportionNON, Alpha, SupportVectorLabels, KernelScale,
    SupportVectors, Bias);
  SupportVectors->canFreeData = false;
  emxFree_real_T(&SupportVectors);
  SupportVectorLabels->canFreeData = false;
  emxFree_real_T(&SupportVectorLabels);
  Alpha->canFreeData = false;
  emxFree_real_T(&Alpha);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/* End of code generation (_coder_run_perception_module_for_srcgen_api.c) */
