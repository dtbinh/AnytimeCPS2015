/*
 * ind2sub.c
 *
 * Code generation for function 'ind2sub'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "ind2sub.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "mod.h"
#include "assert.h"
#include "run_perception_module_for_srcgen_mexutil.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRSInfo sb_emlrtRSI = { 38, "ind2sub",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\elmat\\ind2sub.m"
};

static emlrtRTEInfo x_emlrtRTEI = { 26, 22, "ind2sub",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\elmat\\ind2sub.m"
};

static emlrtRTEInfo y_emlrtRTEI = { 42, 5, "ind2sub",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\elmat\\ind2sub.m"
};

/* Function Declarations */
static boolean_T allinrange(void);

/* Function Definitions */
static boolean_T allinrange(void)
{
  return true;
}

void ind2sub_indexClass(const emlrtStack *sp, const emxArray_real_T *ndx,
  emxArray_int32_T *varargout_1, emxArray_int32_T *varargout_2)
{
  int32_T i10;
  int32_T loop_ub;
  emxArray_int32_T *vk;
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);
  i10 = varargout_1->size[0];
  varargout_1->size[0] = ndx->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)varargout_1, i10, (int32_T)sizeof
                    (int32_T), &x_emlrtRTEI);
  loop_ub = ndx->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    varargout_1->data[i10] = (int32_T)ndx->data[i10];
  }

  st.site = &sb_emlrtRSI;
  b_assert(&st, allinrange());
  i10 = varargout_1->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)varargout_1, i10, (int32_T)sizeof
                    (int32_T), &x_emlrtRTEI);
  loop_ub = varargout_1->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    varargout_1->data[i10]--;
  }

  emxInit_int32_T(sp, &vk, 1, &y_emlrtRTEI, true);
  i10 = vk->size[0];
  vk->size[0] = varargout_1->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)vk, i10, (int32_T)sizeof(int32_T),
                    &x_emlrtRTEI);
  loop_ub = varargout_1->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    st.site = &ff_emlrtRSI;
    vk->data[i10] = div_s32(&st, varargout_1->data[i10], 1200);
  }

  i10 = varargout_2->size[0];
  varargout_2->size[0] = vk->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)varargout_2, i10, (int32_T)sizeof
                    (int32_T), &x_emlrtRTEI);
  loop_ub = vk->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    varargout_2->data[i10] = vk->data[i10] + 1;
  }

  i10 = varargout_1->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)varargout_1, i10, (int32_T)sizeof
                    (int32_T), &x_emlrtRTEI);
  loop_ub = varargout_1->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    varargout_1->data[i10] -= vk->data[i10] * 1200;
  }

  emxFree_int32_T(&vk);
  i10 = varargout_1->size[0];
  emxEnsureCapacity(sp, (emxArray__common *)varargout_1, i10, (int32_T)sizeof
                    (int32_T), &x_emlrtRTEI);
  loop_ub = varargout_1->size[0];
  for (i10 = 0; i10 < loop_ub; i10++) {
    varargout_1->data[i10]++;
  }

  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (ind2sub.c) */
