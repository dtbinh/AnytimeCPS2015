/*
 * File: preprocess_img.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "preprocess_img.h"
#include "rdivide.h"
#include "repmat.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "sum.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Declarations */
static int compute_nones(const boolean_T x[1920000]);
static void eml_li_find(const boolean_T x[1920000], emxArray_int32_T *y);

/* Function Definitions */

/*
 * Arguments    : const boolean_T x[1920000]
 * Return Type  : int
 */
static int compute_nones(const boolean_T x[1920000])
{
  int k;
  int i;
  k = 0;
  for (i = 0; i < 1920000; i++) {
    if (x[i]) {
      k++;
    }
  }

  return k;
}

/*
 * Arguments    : const boolean_T x[1920000]
 *                emxArray_int32_T *y
 * Return Type  : void
 */
static void eml_li_find(const boolean_T x[1920000], emxArray_int32_T *y)
{
  int j;
  int i;
  j = y->size[0];
  y->size[0] = compute_nones(x);
  emxEnsureCapacity((emxArray__common *)y, j, (int)sizeof(int));
  j = 0;
  for (i = 0; i < 1920000; i++) {
    if (x[i]) {
      y->data[j] = i + 1;
      j++;
    }
  }
}

/*
 * Arguments    : const unsigned char I[5760000]
 *                double J[5760000]
 * Return Type  : void
 */
void preprocess_img(const unsigned char I[5760000], double J[5760000])
{
  int i0;
  static double s[1920000];
  static boolean_T b_s[1920000];
  static boolean_T c_s[1920000];
  static boolean_T S[5760000];
  emxArray_int32_T *r0;
  int loop_ub;
  static double dv1[5760000];
  static double dv2[5760000];
  for (i0 = 0; i0 < 5760000; i0++) {
    /*  Remove the NaNs to avoid weirdness when computing probabilities  */
    J[i0] = I[i0];
  }

  /*  Normalize */
  sum(J, s);
  for (i0 = 0; i0 < 1920000; i0++) {
    b_s[i0] = (s[i0] == 0.0);
    c_s[i0] = (s[i0] == 0.0);
  }

  repmat(b_s, S);
  emxInit_int32_T(&r0, 1);
  eml_li_find(c_s, r0);
  loop_ub = r0->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    s[r0->data[i0] - 1] = 1.0;
  }

  emxFree_int32_T(&r0);
  b_repmat(s, dv1);
  rdivide(J, dv1, dv2);
  for (i0 = 0; i0 < 5760000; i0++) {
    J[i0] = (double)S[i0] * J[i0] + (double)!S[i0] * dv2[i0];
  }
}

/*
 * File trailer for preprocess_img.c
 *
 * [EOF]
 */
