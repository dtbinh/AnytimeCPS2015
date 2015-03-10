/*
 * File: _coder_run_perception_module_for_srcgen_api.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "_coder_run_perception_module_for_srcgen_api.h"

/* Function Declarations */
static uint8_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *Im, const
  char_T *identifier))[5760000];
static uint8_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[5760000];
static uint8_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *colors,
  const char_T *identifier))[3];
static uint8_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3];
static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *minAcceptanceProbScalingFactor, const char_T *identifier);
static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *muPOI,
  const char_T *identifier))[12];
static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[12];
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *SigmaPOI,
  const char_T *identifier))[36];
static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[36];
static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *ComponentProportionPOI, const char_T *identifier))[4];
static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[4];
static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Alpha, const
  char_T *identifier, emxArray_real_T *y);
static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *SupportVectors, const char_T *identifier, emxArray_real_T *y);
static void p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static uint8_T (*q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[5760000];
static uint8_T (*r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3];
static real_T s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T (*t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[12];
static real_T (*u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[36];
static real_T (*v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4];
static void w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush);
static void emxFree_real_T(emxArray_real_T **pEmxArray);

/* Function Definitions */

/*
 * Arguments    : emlrtContext *aContext
 * Return Type  : void
 */
void run_perception_module_for_srcgen_initialize(emlrtContext *aContext)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, aContext, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void run_perception_module_for_srcgen_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void run_perception_module_for_srcgen_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  run_perception_module_for_srcgen_xil_terminate();
}

/*
 * Arguments    : const mxArray *prhs[16]
 * Return Type  : void
 */
void run_perception_module_for_srcgen_api(const mxArray *prhs[16])
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
  emxInit_real_T(&st, &Alpha, 2, true);
  emxInit_real_T(&st, &SupportVectorLabels, 2, true);
  emxInit_real_T(&st, &SupportVectors, 2, true);
  prhs[0] = emlrtProtectR2012b(prhs[0], 0, false, -1);
  prhs[1] = emlrtProtectR2012b(prhs[1], 1, false, -1);
  prhs[5] = emlrtProtectR2012b(prhs[5], 5, false, -1);
  prhs[6] = emlrtProtectR2012b(prhs[6], 6, false, -1);
  prhs[7] = emlrtProtectR2012b(prhs[7], 7, false, -1);
  prhs[8] = emlrtProtectR2012b(prhs[8], 8, false, -1);
  prhs[9] = emlrtProtectR2012b(prhs[9], 9, false, -1);
  prhs[10] = emlrtProtectR2012b(prhs[10], 10, false, -1);
  prhs[11] = emlrtProtectR2012b(prhs[11], 11, false, -1);
  prhs[12] = emlrtProtectR2012b(prhs[12], 12, false, -1);
  prhs[14] = emlrtProtectR2012b(prhs[14], 14, false, -1);

  /* Marshall function inputs */
  Im = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "Im");
  colors = c_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "colors");
  minAcceptanceProbScalingFactor = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]),
    "minAcceptanceProbScalingFactor");
  minSignificanceProb = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]),
    "minSignificanceProb");
  minAcceptanceProb = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]),
    "minAcceptanceProb");
  muPOI = g_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "muPOI");
  SigmaPOI = i_emlrt_marshallIn(&st, emlrtAlias(prhs[6]), "SigmaPOI");
  ComponentProportionPOI = k_emlrt_marshallIn(&st, emlrtAlias(prhs[7]),
    "ComponentProportionPOI");
  muNON = g_emlrt_marshallIn(&st, emlrtAlias(prhs[8]), "muNON");
  SigmaNON = i_emlrt_marshallIn(&st, emlrtAlias(prhs[9]), "SigmaNON");
  ComponentProportionNON = k_emlrt_marshallIn(&st, emlrtAlias(prhs[10]),
    "ComponentProportionNON");
  m_emlrt_marshallIn(&st, emlrtAlias(prhs[11]), "Alpha", Alpha);
  m_emlrt_marshallIn(&st, emlrtAlias(prhs[12]), "SupportVectorLabels",
                     SupportVectorLabels);
  KernelScale = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[13]), "KernelScale");
  o_emlrt_marshallIn(&st, emlrtAlias(prhs[14]), "SupportVectors", SupportVectors);
  Bias = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[15]), "Bias");

  /* Invoke the target function */
  run_perception_module_for_srcgen(*Im, *colors, minAcceptanceProbScalingFactor,
    minSignificanceProb, minAcceptanceProb, *muPOI, *SigmaPOI,
    *ComponentProportionPOI, *muNON, *SigmaNON, *ComponentProportionNON, Alpha,
    SupportVectorLabels, KernelScale, SupportVectors, Bias);
  SupportVectors->canFreeData = false;
  emxFree_real_T(&SupportVectors);
  SupportVectorLabels->canFreeData = false;
  emxFree_real_T(&SupportVectorLabels);
  Alpha->canFreeData = false;
  emxFree_real_T(&Alpha);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *Im
 *                const char_T *identifier
 * Return Type  : uint8_T (*)[5760000]
 */
static uint8_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *Im, const
  char_T *identifier))[5760000]
{
  uint8_T (*y)[5760000];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = b_emlrt_marshallIn(sp, emlrtAlias(Im), &thisId);
  emlrtDestroyArray(&Im);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : uint8_T (*)[5760000]
 */
  static uint8_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[5760000]
{
  uint8_T (*y)[5760000];
  y = q_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *colors
 *                const char_T *identifier
 * Return Type  : uint8_T (*)[3]
 */
static uint8_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *colors,
  const char_T *identifier))[3]
{
  uint8_T (*y)[3];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = d_emlrt_marshallIn(sp, emlrtAlias(colors), &thisId);
  emlrtDestroyArray(&colors);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : uint8_T (*)[3]
 */
  static uint8_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[3]
{
  uint8_T (*y)[3];
  y = r_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *minAcceptanceProbScalingFactor
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *minAcceptanceProbScalingFactor, const char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = f_emlrt_marshallIn(sp, emlrtAlias(minAcceptanceProbScalingFactor), &thisId);
  emlrtDestroyArray(&minAcceptanceProbScalingFactor);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = s_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *muPOI
 *                const char_T *identifier
 * Return Type  : real_T (*)[12]
 */
static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *muPOI,
  const char_T *identifier))[12]
{
  real_T (*y)[12];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = h_emlrt_marshallIn(sp, emlrtAlias(muPOI), &thisId);
  emlrtDestroyArray(&muPOI);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[12]
 */
  static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[12]
{
  real_T (*y)[12];
  y = t_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *SigmaPOI
 *                const char_T *identifier
 * Return Type  : real_T (*)[36]
 */
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *SigmaPOI,
  const char_T *identifier))[36]
{
  real_T (*y)[36];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = j_emlrt_marshallIn(sp, emlrtAlias(SigmaPOI), &thisId);
  emlrtDestroyArray(&SigmaPOI);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[36]
 */
  static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[36]
{
  real_T (*y)[36];
  y = u_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *ComponentProportionPOI
 *                const char_T *identifier
 * Return Type  : real_T (*)[4]
 */
static real_T (*k_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *ComponentProportionPOI, const char_T *identifier))[4]
{
  real_T (*y)[4];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  y = l_emlrt_marshallIn(sp, emlrtAlias(ComponentProportionPOI), &thisId);
  emlrtDestroyArray(&ComponentProportionPOI);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[4]
 */
  static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[4]
{
  real_T (*y)[4];
  y = v_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *Alpha
 *                const char_T *identifier
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *Alpha, const
  char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  n_emlrt_marshallIn(sp, emlrtAlias(Alpha), &thisId, y);
  emlrtDestroyArray(&Alpha);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  w_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *SupportVectors
 *                const char_T *identifier
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void o_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *SupportVectors, const char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  p_emlrt_marshallIn(sp, emlrtAlias(SupportVectors), &thisId, y);
  emlrtDestroyArray(&SupportVectors);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void p_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  x_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : uint8_T (*)[5760000]
 */
static uint8_T (*q_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[5760000]
{
  uint8_T (*ret)[5760000];
  int32_T iv0[3];
  int32_T i;
  static const int16_T iv1[3] = { 1200, 1600, 3 };

  for (i = 0; i < 3; i++) {
    iv0[i] = iv1[i];
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "uint8", false, 3U, iv0);
  ret = (uint8_T (*)[5760000])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : uint8_T (*)[3]
 */
  static uint8_T (*r_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[3]
{
  uint8_T (*ret)[3];
  int32_T iv2[2];
  int32_T i0;
  for (i0 = 0; i0 < 2; i0++) {
    iv2[i0] = 1 + (i0 << 1);
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "uint8", false, 2U, iv2);
  ret = (uint8_T (*)[3])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T s_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, 0);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[12]
 */
static real_T (*t_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[12]
{
  real_T (*ret)[12];
  int32_T iv3[2];
  int32_T i1;
  for (i1 = 0; i1 < 2; i1++) {
    iv3[i1] = 4 - i1;
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv3);
  ret = (real_T (*)[12])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[36]
 */
  static real_T (*u_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[36]
{
  real_T (*ret)[36];
  int32_T iv4[3];
  int32_T i;
  static const int8_T iv5[3] = { 3, 3, 4 };

  for (i = 0; i < 3; i++) {
    iv4[i] = iv5[i];
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 3U, iv4);
  ret = (real_T (*)[36])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[4]
 */
static real_T (*v_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[4]
{
  real_T (*ret)[4];
  int32_T iv6[2];
  int32_T i2;
  for (i2 = 0; i2 < 2; i2++) {
    iv6[i2] = 1 + 3 * i2;
  }

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv6);
  ret = (real_T (*)[4])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
  static void w_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  int32_T iv7[2];
  boolean_T bv0[2];
  int32_T i3;
  static const boolean_T bv1[2] = { false, true };

  int32_T iv8[2];
  for (i3 = 0; i3 < 2; i3++) {
    iv7[i3] = 1 + -2 * i3;
    bv0[i3] = bv1[i3];
  }

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv7, bv0, iv8);
  ret->size[0] = iv8[0];
  ret->size[1] = iv8[1];
  ret->allocatedSize = ret->size[0] * ret->size[1];
  ret->data = (real_T *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                emxArray_real_T *ret
 * Return Type  : void
 */
static void x_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  int32_T iv9[2];
  boolean_T bv2[2];
  int32_T i4;
  static const boolean_T bv3[2] = { true, false };

  int32_T iv10[2];
  for (i4 = 0; i4 < 2; i4++) {
    iv9[i4] = (i4 << 2) - 1;
    bv2[i4] = bv3[i4];
  }

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, iv9, bv2, iv10);
  ret->size[0] = iv10[0];
  ret->size[1] = iv10[1];
  ret->allocatedSize = ret->size[0] * ret->size[1];
  ret->data = (real_T *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                emxArray_real_T **pEmxArray
 *                int32_T numDimensions
 *                boolean_T doPush
 * Return Type  : void
 */
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2012b(sp, (void *)pEmxArray, (void (*)(void *))
      emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex((uint32_T)(sizeof(int32_T)
    * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 * Return Type  : void
 */
static void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex((void *)(*pEmxArray)->data);
    }

    emlrtFreeMex((void *)(*pEmxArray)->size);
    emlrtFreeMex((void *)*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

/*
 * File trailer for _coder_run_perception_module_for_srcgen_api.c
 *
 * [EOF]
 */
