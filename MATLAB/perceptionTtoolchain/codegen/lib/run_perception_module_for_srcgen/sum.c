/*
 * File: sum.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "sum.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */

/*
 * Arguments    : const double x[7680000]
 *                double y[1920000]
 * Return Type  : void
 */
void b_sum(const double x[7680000], double y[1920000])
{
  int iy;
  int ixstart;
  int j;
  int ix;
  double s;
  int k;
  iy = -1;
  ixstart = -1;
  for (j = 0; j < 1920000; j++) {
    ixstart++;
    ix = ixstart;
    s = x[ixstart];
    for (k = 0; k < 3; k++) {
      ix += 1920000;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                double y[2]
 * Return Type  : void
 */
void c_sum(const emxArray_real_T *x, double y[2])
{
  int ixstart;
  int ix;
  int iy;
  int i;
  double s;
  if (x->size[0] == 0) {
    for (ixstart = 0; ixstart < 2; ixstart++) {
      y[ixstart] = 0.0;
    }
  } else {
    ix = -1;
    iy = -1;
    for (i = 0; i < 2; i++) {
      ixstart = ix + 1;
      ix++;
      s = x->data[ixstart];
      for (ixstart = 2; ixstart <= x->size[0]; ixstart++) {
        ix++;
        s += x->data[ix];
      }

      iy++;
      y[iy] = s;
    }
  }
}

/*
 * Arguments    : const double x[5760000]
 *                double y[1920000]
 * Return Type  : void
 */
void sum(const double x[5760000], double y[1920000])
{
  int iy;
  int ixstart;
  int j;
  int ix;
  double s;
  int k;
  iy = -1;
  ixstart = -1;
  for (j = 0; j < 1920000; j++) {
    ixstart++;
    ix = ixstart;
    s = x[ixstart];
    for (k = 0; k < 2; k++) {
      ix += 1920000;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
