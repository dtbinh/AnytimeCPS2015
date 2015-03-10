/*
 * medfilt2.c
 *
 * Code generation for function 'medfilt2'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "medfilt2.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "mod.h"
#include "padarray.h"
#include "run_perception_module_for_srcgen_mexutil.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRSInfo nb_emlrtRSI = { 34, "medfilt2",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\medfilt2.m"
};

static emlrtRSInfo ob_emlrtRSI = { 84, "ordfilt2",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\ordfilt2.m"
};

static emlrtRSInfo pb_emlrtRSI = { 109, "ordfilt2",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\ordfilt2.m"
};

static emlrtRSInfo qb_emlrtRSI = { 130, "ordfilt2",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\ordfilt2.m"
};

static emlrtRSInfo vb_emlrtRSI = { 101, "ordfilt2",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\ordfilt2.m"
};

static emlrtRTEInfo g_emlrtRTEI = { 95, 5, "ordfilt2",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\ordfilt2.m"
};

static emlrtBCInfo l_emlrtBCI = { 1, 9, 84, 10, "", "ordfilt2",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\images\\images\\eml\\ordfilt2.m",
  0 };

/* Function Definitions */
void medfilt2(const emlrtStack *sp, const boolean_T varargin_1[1920000],
              boolean_T b[1920000])
{
  int8_T c[9];
  real_T r[9];
  int32_T b_index;
  int32_T i;
  int32_T vk;
  real_T y[9];
  real_T padSize;
  real_T b_padSize[2];
  emxArray_boolean_T *Apad;
  int32_T offsets[9];
  real_T d0;
  real_T startIdx[2];
  real_T domainSize[2];
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
  st.site = &nb_emlrtRSI;
  b_index = 1;
  for (i = 0; i < 9; i++) {
    b_st.site = &ob_emlrtRSI;
    c_st.site = &rb_emlrtRSI;
    d_st.site = &ff_emlrtRSI;
    vk = div_s32(&d_st, i, 3);
    r[emlrtDynamicBoundsCheckFastR2012b(b_index, 1, 9, &l_emlrtBCI, &st) - 1] =
      (real_T)(i - vk * 3) + 1.0;
    c[b_index - 1] = (int8_T)(vk + 1);
    b_index++;
  }

  for (b_index = 0; b_index < 9; b_index++) {
    y[b_index] = muDoubleScalarAbs(r[b_index] - 2.0);
    r[b_index] -= 2.0;
    c[b_index] = (int8_T)(c[b_index] - 2);
  }

  padSize = y[0];
  for (b_index = 1; b_index + 1 < 10; b_index++) {
    if (y[b_index] > padSize) {
      padSize = y[b_index];
    }
  }

  for (b_index = 0; b_index < 9; b_index++) {
    y[b_index] = muDoubleScalarAbs(c[b_index]);
  }

  i = (int32_T)y[0];
  for (b_index = 1; b_index + 1 < 10; b_index++) {
    if ((int32_T)y[b_index] > i) {
      i = (int32_T)y[b_index];
    }
  }

  padSize = muDoubleScalarMax(padSize, i);
  for (b_index = 0; b_index < 2; b_index++) {
    b_padSize[b_index] = padSize;
  }

  b_emxInit_boolean_T(&st, &Apad, 2, &g_emlrtRTEI, true);
  b_st.site = &vb_emlrtRSI;
  padarray(&b_st, varargin_1, b_padSize, Apad);
  i = Apad->size[0];
  for (b_index = 0; b_index < 9; b_index++) {
    d0 = muDoubleScalarRound((real_T)c[b_index] * (real_T)i + r[b_index]);
    if (d0 < 2.147483648E+9) {
      if (d0 >= -2.147483648E+9) {
        vk = (int32_T)d0;
      } else {
        vk = MIN_int32_T;
      }
    } else {
      vk = MAX_int32_T;
    }

    offsets[b_index] = vk;
  }

  for (b_index = 0; b_index < 9; b_index++) {
    b_st.site = &pb_emlrtRSI;
  }

  startIdx[0] = padSize;
  startIdx[1] = padSize;
  b_st.site = &qb_emlrtRSI;
  for (b_index = 0; b_index < 2; b_index++) {
    domainSize[b_index] = 3.0;
    b_padSize[b_index] = 1200.0 + 400.0 * (real_T)b_index;
  }

  ordfilt2_boolean(&Apad->data[0], (real_T)Apad->size[0], startIdx, offsets, 9.0,
                   domainSize, 4.0, b, b_padSize);
  emxFree_boolean_T(&Apad);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (medfilt2.c) */
