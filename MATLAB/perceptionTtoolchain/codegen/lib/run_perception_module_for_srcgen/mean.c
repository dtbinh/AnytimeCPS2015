/*
 * File: mean.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "mean.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                double y[2]
 * Return Type  : void
 */
void mean(const emxArray_real_T *x, double y[2])
{
  int ixstart;
  int ix;
  int iy;
  int i;
  double s;
  int k;
  if (x->size[0] == 0) {
    for (ixstart = 0; ixstart < 2; ixstart++) {
      y[ixstart] = 0.0;
    }
  } else {
    ix = 0;
    iy = -1;
    for (i = 0; i < 2; i++) {
      ixstart = ix;
      ix++;
      s = x->data[ixstart];
      for (k = 2; k <= x->size[0]; k++) {
        ix++;
        s += x->data[ix - 1];
      }

      iy++;
      y[iy] = s;
    }
  }

  k = x->size[0];
  for (ixstart = 0; ixstart < 2; ixstart++) {
    y[ixstart] /= (double)k;
  }
}

/*
 * File trailer for mean.c
 *
 * [EOF]
 */
