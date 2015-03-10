/*
 * mean.c
 *
 * Code generation for function 'mean'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "mean.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */
void mean(const emxArray_real_T *x, real_T y[2])
{
  int32_T ixstart;
  int32_T ix;
  int32_T iy;
  int32_T i;
  real_T s;
  int32_T k;
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
    y[ixstart] /= (real_T)k;
  }
}

/* End of code generation (mean.c) */
