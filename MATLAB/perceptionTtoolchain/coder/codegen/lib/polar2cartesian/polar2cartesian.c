/*
 * File: polar2cartesian.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 02-Mar-2015 20:01:11
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "polar2cartesian.h"

/* Function Definitions */

/*
 * Convert polar to Cartesian
 * Arguments    : double r
 *                double theta
 *                double *x
 *                double *y
 * Return Type  : void
 */
void polar2cartesian(double r, double theta, double *x, double *y)
{
  /* 'polar2cartesian:4' x = r * cos(theta); */
  *x = r * cos(theta);

  /* 'polar2cartesian:5' y = r * sin(theta); */
  *y = r * sin(theta);
}

/*
 * File trailer for polar2cartesian.c
 *
 * [EOF]
 */
