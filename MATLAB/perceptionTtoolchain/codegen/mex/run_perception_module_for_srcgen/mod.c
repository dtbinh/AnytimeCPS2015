/*
 * mod.c
 *
 * Code generation for function 'mod'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "mod.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "run_perception_module_for_srcgen_mexutil.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRTEInfo m_emlrtRTEI = { 1, 1, "scalexpAlloc",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\coder\\coder\\+coder\\+internal\\scalexpAlloc.p"
};

static emlrtRSInfo ef_emlrtRSI = { 104, "mod",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\elfun\\mod.m" };

/* Function Definitions */
void b_mod(const emlrtStack *sp, const emxArray_real_T *x, real_T y,
           emxArray_real_T *r)
{
  uint32_T uv0[2];
  int32_T k;
  real_T b_r;
  for (k = 0; k < 2; k++) {
    uv0[k] = (uint32_T)x->size[k];
  }

  k = r->size[0] * r->size[1];
  r->size[0] = 1;
  r->size[1] = (int32_T)uv0[1];
  emxEnsureCapacity(sp, (emxArray__common *)r, k, (int32_T)sizeof(real_T),
                    &m_emlrtRTEI);
  for (k = 0; k < (int32_T)uv0[1]; k++) {
    if (y == muDoubleScalarFloor(y)) {
      b_r = x->data[k] - muDoubleScalarFloor(x->data[k] / y) * y;
    } else {
      b_r = x->data[k] / y;
      if (muDoubleScalarAbs(b_r - muDoubleScalarRound(b_r)) <=
          2.2204460492503131E-16 * muDoubleScalarAbs(b_r)) {
        b_r = 0.0;
      } else {
        b_r = (b_r - muDoubleScalarFloor(b_r)) * y;
      }
    }

    r->data[k] = b_r;
  }
}

int32_T c_mod(const emlrtStack *sp, int32_T x)
{
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &ef_emlrtRSI;
  return x - div_s32(&st, x, 10) * 10;
}

/* End of code generation (mod.c) */
