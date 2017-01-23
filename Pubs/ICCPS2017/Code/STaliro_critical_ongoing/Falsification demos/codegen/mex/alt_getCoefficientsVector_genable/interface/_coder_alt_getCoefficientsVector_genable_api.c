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
static emlrtRTEInfo e_emlrtRTEI = { 1, 1,
  "_coder_alt_getCoefficientsVector_genable_api", "" };

/* Function Declarations */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[81];
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *dist_array_xy, const char_T *identifier))[6561];
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[6561];
static const mxArray *d_emlrt_marshallOut(const emxArray_real_T *u);
static real_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *dx, const
  char_T *identifier);
static const mxArray *e_emlrt_marshallOut(const emxArray_real_T *u);
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *grid_x,
  const char_T *identifier))[81];
static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *E_dash,
  const char_T *identifier))[8];
static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[8];
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[81];
static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[6561];
static real_T k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[8];

/* Function Definitions */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[81]
{
  real_T (*y)[81];
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *dist_array_xy, const char_T *identifier))[6561]
{
  real_T (*y)[6561];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(dist_array_xy), &thisId);
  emlrtDestroyArray(&dist_array_xy);
  return y;
}

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[6561]
{
  real_T (*y)[6561];
  y = j_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static const mxArray *d_emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  static const int32_T iv5[3] = { 0, 0, 0 };

  const mxArray *m5;
  y = NULL;
  m5 = emlrtCreateNumericArray(3, iv5, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m5, (void *)u->data);
  emlrtSetDimensions((mxArray *)m5, u->size, 3);
  emlrtAssign(&y, m5);
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

  const mxArray *m6;
  y = NULL;
  m6 = emlrtCreateNumericArray(3, iv6, mxDOUBLE_CLASS, mxREAL);
  mxSetData((mxArray *)m6, (void *)u->data);
  emlrtSetDimensions((mxArray *)m6, u->size, 3);
  emlrtAssign(&y, m6);
  return y;
}

static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *grid_x,
  const char_T *identifier))[81]
{
  real_T (*y)[81];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(grid_x), &thisId);
  emlrtDestroyArray(&grid_x);
  return y;
}
  static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = k_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *E_dash,
  const char_T *identifier))[8]
{
  real_T (*y)[8];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = h_emlrt_marshallIn(sp, emlrtAlias(E_dash), &thisId);
  emlrtDestroyArray(&E_dash);
  return y;
}
  static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[8]
{
  real_T (*y)[8];
  y = l_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[81]
{
  real_T (*ret)[81];
  static const int32_T dims[2] = { 1, 81 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[81])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[6561]
{
  real_T (*ret)[6561];
  static const int32_T dims[2] = { 81, 81 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[6561])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[8]
{
  real_T (*ret)[8];
  static const int32_T dims[2] = { 4, 2 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[8])mxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  void alt_getCoefficientsVector_genable_api(const mxArray * const prhs[9],
  const mxArray *plhs[2])
{
  emxArray_real_T *C_00k;
  emxArray_real_T *D_ejk;
  real_T (*grid_x)[81];
  real_T (*dist_array_xy)[6561];
  real_T dx;
  real_T j_min;
  real_T j_max;
  real_T k_min;
  real_T k_max;
  real_T (*E_dash)[8];
  real_T viz;
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_real_T1(&st, &C_00k, 3, &e_emlrtRTEI, true);
  emxInit_real_T1(&st, &D_ejk, 3, &e_emlrtRTEI, true);

  /* Marshall function inputs */
  grid_x = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "grid_x");
  dist_array_xy = c_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "dist_array_xy");
  dx = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "dx");
  j_min = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "j_min");
  j_max = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "j_max");
  k_min = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "k_min");
  k_max = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "k_max");
  E_dash = g_emlrt_marshallIn(&st, emlrtAlias(prhs[7]), "E_dash");
  viz = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "viz");

  /* Invoke the target function */
  alt_getCoefficientsVector_genable(&st, *grid_x, *dist_array_xy, dx, j_min,
    j_max, k_min, k_max, *E_dash, viz, C_00k, D_ejk);

  /* Marshall function outputs */
  plhs[0] = d_emlrt_marshallOut(C_00k);
  plhs[1] = e_emlrt_marshallOut(D_ejk);
  D_ejk->canFreeData = false;
  emxFree_real_T(&D_ejk);
  C_00k->canFreeData = false;
  emxFree_real_T(&C_00k);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

/* End of code generation (_coder_alt_getCoefficientsVector_genable_api.c) */
