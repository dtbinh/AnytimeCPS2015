/*
 * File: norm.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 02-Mar-2015 20:10:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "matrix_exp.h"
#include "norm.h"

/* Function Definitions */

/*
 * Arguments    : const double x[25600]
 * Return Type  : double
 */
double norm(const double x[25600])
{
  double y;
  int j;
  boolean_T exitg1;
  double s;
  int i;
  y = 0.0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j < 160)) {
    s = 0.0;
    for (i = 0; i < 160; i++) {
      s += fabs(x[i + 160 * j]);
    }

    if (rtIsNaN(s)) {
      y = rtNaN;
      exitg1 = true;
    } else {
      if (s > y) {
        y = s;
      }

      j++;
    }
  }

  return y;
}

/*
 * File trailer for norm.c
 *
 * [EOF]
 */
