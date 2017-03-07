/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_alt_getCoefficientsVector_genable_api.c
 *
 * Code generation for function '_coder_alt_getCoefficientsVector_genable_api'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "alt_getCoefficientsVector_genable.h"
#include "_coder_alt_getCoefficientsVector_genable_api.h"
#include "alt_getCoefficientsVector_genable_emxutil.h"
#include "alt_getCoefficientsVector_genable_data.h"

/* Variable Definitions */
static emlrtRTEInfo o_emlrtRTEI = { 1, 1,
  "_coder_alt_getCoefficientsVector_genable_api", "" };

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *dist_array_xy, const char_T *identifier, emxArray_real_T *y);
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static const mxArray *d_emlrt_marshallOut(const emxArray_real_T *u);
static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *dx, const
  char_T *identifier);
static const mxArray *e_emlrt_marshallOut(const emxArray_real_T *u);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *grid_x, const
  char_T *identifier, emxArray_real_T *y);
static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static real_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);

/* Function Definitions */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  g_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *dist_array_xy, const char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(sp, emlrtAlias(dist_array_xy), &thisId, y);
  emlrtDestroyArray(&dist_array_xy);
}

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  h_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *d_emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  static const int32_T iv5[3] = { 0, 0, 0 };

  const mxArray *m4;
  y = NULL;
  m4 = emlrtCreateNumericArray(3, iv5, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m4, (void *)u->data);
  emlrtSetDimensions((mxArray *)m4, u->size, 3);
  emlrtAssign(&y, m4);
  return y;
}

static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *dx, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(dx), &thisId);
  emlrtDestroyArray(&dx);
  return y;
}

static const mxArray *e_emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  static const int32_T iv6[3] = { 0, 0, 0 };

  const mxArray *m5;
  y = NULL;
  m5 = emlrtCreateNumericArray(3, iv6, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m5, (void *)u->data);
  emlrtSetDimensions((mxArray *)m5, u->size, 3);
  emlrtAssign(&y, m5);
  return y;
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *grid_x, const
  char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(grid_x), &thisId, y);
  emlrtDestroyArray(&grid_x);
}

static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  int32_T iv7[2];
  boolean_T bv0[2] = { false, true };

  static const int32_T dims[2] = { 1, -1 };

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims, &bv0[0],
    iv7);
  ret->size[0] = iv7[0];
  ret->size[1] = iv7[1];
  ret->allocatedSize = ret->size[0] * ret->size[1];
  ret->data = (real_T *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  int32_T iv8[2];
  boolean_T bv1[2] = { true, true };

  static const int32_T dims[2] = { -1, -1 };

  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims, &bv1[0],
    iv8);
  ret->size[0] = iv8[0];
  ret->size[1] = iv8[1];
  ret->allocatedSize = ret->size[0] * ret->size[1];
  ret->data = (real_T *)mxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static real_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void alt_getCoefficientsVector_genable_api(const mxArray * const prhs[9], const
  mxArray *plhs[2])
{
  emxArray_real_T *grid_x;
  emxArray_real_T *dist_array_xy;
  emxArray_real_T *E_dash;
  emxArray_real_T *C_00k;
  emxArray_real_T *D_ejk;
  real_T dx;
  real_T j_min;
  real_T j_max;
  real_T k_min;
  real_T k_max;
  real_T viz;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_real_T(&st, &grid_x, 2, &o_emlrtRTEI, true);
  emxInit_real_T(&st, &dist_array_xy, 2, &o_emlrtRTEI, true);
  emxInit_real_T(&st, &E_dash, 2, &o_emlrtRTEI, true);
  emxInit_real_T2(&st, &C_00k, 3, &o_emlrtRTEI, true);
  emxInit_real_T2(&st, &D_ejk, 3, &o_emlrtRTEI, true);

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "grid_x", grid_x);
  c_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "dist_array_xy", dist_array_xy);
  dx = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "dx");
  j_min = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "j_min");
  j_max = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "j_max");
  k_min = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "k_min");
  k_max = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "k_max");
  c_emlrt_marshallIn(&st, emlrtAlias(prhs[7]), "E_dash", E_dash);
  viz = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "viz");

  /* Invoke the target function */
  alt_getCoefficientsVector_genable(&st, grid_x, dist_array_xy, dx, j_min, j_max,
    k_min, k_max, E_dash, viz, C_00k, D_ejk);

  /* Marshall function outputs */
  plhs[0] = d_emlrt_marshallOut(C_00k);
  plhs[1] = e_emlrt_marshallOut(D_ejk);
  D_ejk->canFreeData = false;
  emxFree_real_T(&D_ejk);
  C_00k->canFreeData = false;
  emxFree_real_T(&C_00k);
  E_dash->canFreeData = false;
  emxFree_real_T(&E_dash);
  dist_array_xy->canFreeData = false;
  emxFree_real_T(&dist_array_xy);
  grid_x->canFreeData = false;
  emxFree_real_T(&grid_x);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/* End of code generation (_coder_alt_getCoefficientsVector_genable_api.c) */
