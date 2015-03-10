/*
 * File: padarray.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "padarray.h"
#include "medfilt2.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "mod.h"
#include "colon.h"
#include "run_perception_module_for_srcgen_rtwutil.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */

/*
 * Arguments    : const boolean_T varargin_1[1920000]
 *                const double varargin_2[2]
 *                emxArray_boolean_T *b
 * Return Type  : void
 */
void padarray(const boolean_T varargin_1[1920000], const double varargin_2[2],
              emxArray_boolean_T *b)
{
  int sizeB[2];
  double b_varargin_2[2];
  double b_varargin_1[2];
  int i6;
  int ixstart;
  double mtmp;
  int ix;
  boolean_T exitg1;
  emxArray_int32_T *idxA;
  int sizeIdxDir[2];
  emxArray_uint32_T *idxDir;
  emxArray_int32_T *r1;
  emxArray_real_T *y;
  emxArray_real_T *r2;
  emxArray_int32_T *b_idxDir;
  int k;
  boolean_T n_too_large;
  double anew;
  int n;
  double y_data[1600];
  int b_n;
  double b_y_data[1600];
  unsigned int u0;
  unsigned int dimNums_data[3200];
  double apnd;
  double ndbl;
  double cdiff;
  double absa;
  double absb;
  b_varargin_2[0] = varargin_2[0];
  b_varargin_2[1] = varargin_2[1];
  for (i6 = 0; i6 < 2; i6++) {
    b_varargin_1[i6] = 2.0 * b_varargin_2[i6] + (1200.0 + 400.0 * (double)i6);
  }

  ixstart = 1;
  mtmp = b_varargin_1[0];
  if (rtIsNaN(b_varargin_1[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 3)) {
      ixstart = 2;
      if (!rtIsNaN(b_varargin_1[1])) {
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

  b_emxInit_int32_T(&idxA, 2);
  i6 = idxA->size[0] * idxA->size[1];
  idxA->size[0] = (int)mtmp;
  idxA->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)idxA, i6, (int)sizeof(int));
  emxInit_uint32_T(&idxDir, 2);
  emxInit_int32_T(&r1, 1);
  emxInit_real_T(&y, 2);
  emxInit_real_T(&r2, 2);
  b_emxInit_int32_T(&b_idxDir, 2);
  for (k = 0; k < 2; k++) {
    float_colon_length(1200.0 + 400.0 * (double)k, &n, &anew, &mtmp,
                       &n_too_large);
    y_data[0] = anew;
    if (n > 1) {
      y_data[n - 1] = mtmp;
      i6 = n - 1;
      ixstart = i6 / 2;
      for (ix = 1; ix < ixstart; ix++) {
        y_data[ix] = anew + (double)ix;
        y_data[(n - ix) - 1] = mtmp - (double)ix;
      }

      if (ixstart << 1 == n - 1) {
        y_data[ixstart] = (anew + mtmp) / 2.0;
      } else {
        y_data[ixstart] = anew + (double)ixstart;
        y_data[ixstart + 1] = mtmp - (double)ixstart;
      }
    }

    b_float_colon_length(1200.0 + 400.0 * (double)k, &b_n, &anew, &mtmp,
                         &n_too_large);
    b_y_data[0] = anew;
    if (b_n > 1) {
      b_y_data[b_n - 1] = mtmp;
      i6 = b_n - 1;
      ixstart = i6 / 2;
      for (ix = 1; ix < ixstart; ix++) {
        b_y_data[ix] = anew + -(double)ix;
        b_y_data[(b_n - ix) - 1] = mtmp - (-(double)ix);
      }

      if (ixstart << 1 == b_n - 1) {
        b_y_data[ixstart] = (anew + mtmp) / 2.0;
      } else {
        b_y_data[ixstart] = anew + -(double)ixstart;
        b_y_data[ixstart + 1] = mtmp - (-(double)ixstart);
      }
    }

    for (i6 = 0; i6 < n; i6++) {
      mtmp = rt_roundd_snf(y_data[i6]);
      if (mtmp < 4.294967296E+9) {
        if (mtmp >= 0.0) {
          u0 = (unsigned int)mtmp;
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
      mtmp = rt_roundd_snf(b_y_data[i6]);
      if (mtmp < 4.294967296E+9) {
        if (mtmp >= 0.0) {
          u0 = (unsigned int)mtmp;
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

    mtmp = ((1200.0 + 400.0 * (double)k) + varargin_2[k]) - 1.0;
    if (rtIsNaN(-varargin_2[k]) || rtIsNaN(mtmp)) {
      n = 0;
      anew = rtNaN;
      apnd = mtmp;
    } else if (rtIsInf(-varargin_2[k]) || rtIsInf(mtmp)) {
      n = 0;
      anew = rtNaN;
      apnd = mtmp;
    } else {
      anew = -varargin_2[k];
      ndbl = floor((mtmp - (-varargin_2[k])) + 0.5);
      apnd = -varargin_2[k] + ndbl;
      cdiff = apnd - mtmp;
      absa = fabs(-varargin_2[k]);
      absb = fabs(mtmp);
      if ((absa >= absb) || rtIsNaN(absb)) {
        absb = absa;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
        ndbl++;
        apnd = mtmp;
      } else if (cdiff > 0.0) {
        apnd = -varargin_2[k] + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      n = (int)ndbl - 1;
    }

    i6 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n + 1;
    emxEnsureCapacity((emxArray__common *)y, i6, (int)sizeof(double));
    y->data[0] = anew;
    if (n + 1 > 1) {
      y->data[n] = apnd;
      ixstart = n / 2;
      for (ix = 1; ix < ixstart; ix++) {
        y->data[ix] = anew + (double)ix;
        y->data[n - ix] = apnd - (double)ix;
      }

      if (ixstart << 1 == n) {
        y->data[ixstart] = (anew + apnd) / 2.0;
      } else {
        y->data[ixstart] = anew + (double)ixstart;
        y->data[ixstart + 1] = apnd - (double)ixstart;
      }
    }

    b_mod(y, 2.0 * (1200.0 + 400.0 * (double)k), r2);
    i6 = idxDir->size[0] * idxDir->size[1];
    idxDir->size[0] = 1;
    idxDir->size[1] = r2->size[1];
    emxEnsureCapacity((emxArray__common *)idxDir, i6, (int)sizeof(unsigned int));
    ixstart = r2->size[0] * r2->size[1];
    for (i6 = 0; i6 < ixstart; i6++) {
      idxDir->data[i6] = dimNums_data[(int)(r2->data[i6] + 1.0) - 1];
    }

    sizeIdxDir[k] = idxDir->size[1];
    ixstart = sizeIdxDir[k];
    i6 = r1->size[0];
    r1->size[0] = sizeIdxDir[k];
    emxEnsureCapacity((emxArray__common *)r1, i6, (int)sizeof(int));
    for (i6 = 0; i6 < ixstart; i6++) {
      r1->data[i6] = i6;
    }

    i6 = b_idxDir->size[0] * b_idxDir->size[1];
    b_idxDir->size[0] = 1;
    b_idxDir->size[1] = idxDir->size[1];
    emxEnsureCapacity((emxArray__common *)b_idxDir, i6, (int)sizeof(int));
    ixstart = idxDir->size[1];
    for (i6 = 0; i6 < ixstart; i6++) {
      b_idxDir->data[b_idxDir->size[0] * i6] = (int)idxDir->data[idxDir->size[0]
        * i6];
    }

    ixstart = r1->size[0];
    for (i6 = 0; i6 < ixstart; i6++) {
      idxA->data[r1->data[i6] + idxA->size[0] * k] = b_idxDir->data[i6];
    }

    sizeB[k] = (int)((1200.0 + 400.0 * (double)k) + 2.0 * varargin_2[k]);
  }

  emxFree_int32_T(&b_idxDir);
  emxFree_real_T(&r2);
  emxFree_real_T(&y);
  emxFree_int32_T(&r1);
  emxFree_uint32_T(&idxDir);
  i6 = b->size[0] * b->size[1];
  b->size[0] = sizeB[0];
  b->size[1] = sizeB[1];
  emxEnsureCapacity((emxArray__common *)b, i6, (int)sizeof(boolean_T));
  for (ixstart = 0; ixstart < sizeB[1]; ixstart++) {
    i6 = b->size[0];
    for (ix = 0; ix < i6; ix++) {
      b->data[ix + b->size[0] * ixstart] = varargin_1[(idxA->data[ix] + 1200 *
        (idxA->data[ixstart + idxA->size[0]] - 1)) - 1];
    }
  }

  emxFree_int32_T(&idxA);
}

/*
 * File trailer for padarray.c
 *
 * [EOF]
 */
