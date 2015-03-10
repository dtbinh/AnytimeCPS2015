/*
 * File: medfilt2.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "medfilt2.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "padarray.h"
#include "run_perception_module_for_srcgen_rtwutil.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */

/*
 * Arguments    : const boolean_T varargin_1[1920000]
 *                boolean_T b[1920000]
 * Return Type  : void
 */
void medfilt2(const boolean_T varargin_1[1920000], boolean_T b[1920000])
{
  signed char c[9];
  double r[9];
  int b_index;
  int i;
  int vk;
  double y[9];
  double padSize;
  double b_padSize[2];
  emxArray_boolean_T *Apad;
  int offsets[9];
  double d0;
  double startIdx[2];
  double domainSize[2];
  b_index = 0;
  for (i = 0; i < 9; i++) {
    vk = i / 3;
    r[b_index] = (double)(i - vk * 3) + 1.0;
    c[b_index] = (signed char)(vk + 1);
    b_index++;
  }

  for (b_index = 0; b_index < 9; b_index++) {
    y[b_index] = fabs(r[b_index] - 2.0);
    r[b_index] -= 2.0;
    c[b_index] = (signed char)(c[b_index] - 2);
  }

  padSize = y[0];
  for (b_index = 1; b_index + 1 < 10; b_index++) {
    if (y[b_index] > padSize) {
      padSize = y[b_index];
    }
  }

  for (b_index = 0; b_index < 9; b_index++) {
    y[b_index] = fabs(c[b_index]);
  }

  i = (int)y[0];
  for (b_index = 1; b_index + 1 < 10; b_index++) {
    if ((int)y[b_index] > i) {
      i = (int)y[b_index];
    }
  }

  if (padSize >= i) {
  } else {
    padSize = i;
  }

  for (b_index = 0; b_index < 2; b_index++) {
    b_padSize[b_index] = padSize;
  }

  emxInit_boolean_T(&Apad, 2);
  padarray(varargin_1, b_padSize, Apad);
  i = Apad->size[0];
  for (b_index = 0; b_index < 9; b_index++) {
    d0 = rt_roundd_snf((double)c[b_index] * (double)i + r[b_index]);
    if (d0 < 2.147483648E+9) {
      if (d0 >= -2.147483648E+9) {
        vk = (int)d0;
      } else {
        vk = MIN_int32_T;
      }
    } else {
      vk = MAX_int32_T;
    }

    offsets[b_index] = vk;
  }

  startIdx[0] = padSize;
  startIdx[1] = padSize;
  for (b_index = 0; b_index < 2; b_index++) {
    domainSize[b_index] = 3.0;
    b_padSize[b_index] = 1200.0 + 400.0 * (double)b_index;
  }

  ordfilt2_boolean(&Apad->data[0], (double)Apad->size[0], startIdx, offsets, 9.0,
                   domainSize, 4.0, b, b_padSize);
  emxFree_boolean_T(&Apad);
}

/*
 * File trailer for medfilt2.c
 *
 * [EOF]
 */
