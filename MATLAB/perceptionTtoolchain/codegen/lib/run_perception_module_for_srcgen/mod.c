/*
 * File: mod.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "mod.h"
#include "medfilt2.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "run_perception_module_for_srcgen_rtwutil.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                double y
 *                emxArray_real_T *r
 * Return Type  : void
 */
void b_mod(const emxArray_real_T *x, double y, emxArray_real_T *r)
{
  unsigned int uv0[2];
  int k;
  double b_r;
  for (k = 0; k < 2; k++) {
    uv0[k] = (unsigned int)x->size[k];
  }

  k = r->size[0] * r->size[1];
  r->size[0] = 1;
  r->size[1] = (int)uv0[1];
  emxEnsureCapacity((emxArray__common *)r, k, (int)sizeof(double));
  for (k = 0; k < (int)uv0[1]; k++) {
    if (y == floor(y)) {
      b_r = x->data[k] - floor(x->data[k] / y) * y;
    } else {
      b_r = x->data[k] / y;
      if (fabs(b_r - rt_roundd_snf(b_r)) <= 2.2204460492503131E-16 * fabs(b_r))
      {
        b_r = 0.0;
      } else {
        b_r = (b_r - floor(b_r)) * y;
      }
    }

    r->data[k] = b_r;
  }
}

/*
 * File trailer for mod.c
 *
 * [EOF]
 */
