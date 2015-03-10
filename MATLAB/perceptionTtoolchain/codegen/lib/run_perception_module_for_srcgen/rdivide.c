/*
 * File: rdivide.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "rdivide.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */

/*
 * Arguments    : const double x[7680000]
 *                const double y[7680000]
 *                double z[7680000]
 * Return Type  : void
 */
void b_rdivide(const double x[7680000], const double y[7680000], double z
               [7680000])
{
  int i4;
  for (i4 = 0; i4 < 7680000; i4++) {
    z[i4] = x[i4] / y[i4];
  }
}

/*
 * Arguments    : const double x[2]
 *                double y
 *                double z[2]
 * Return Type  : void
 */
void c_rdivide(const double x[2], double y, double z[2])
{
  int i5;
  for (i5 = 0; i5 < 2; i5++) {
    z[i5] = x[i5] / y;
  }
}

/*
 * Arguments    : const double x[5760000]
 *                const double y[5760000]
 *                double z[5760000]
 * Return Type  : void
 */
void rdivide(const double x[5760000], const double y[5760000], double z[5760000])
{
  int i1;
  for (i1 = 0; i1 < 5760000; i1++) {
    z[i1] = x[i1] / y[i1];
  }
}

/*
 * File trailer for rdivide.c
 *
 * [EOF]
 */
