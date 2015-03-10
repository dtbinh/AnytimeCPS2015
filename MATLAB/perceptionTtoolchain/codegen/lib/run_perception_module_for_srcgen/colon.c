/*
 * File: colon.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "colon.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */

/*
 * Arguments    : double a
 *                int *n
 *                double *anew
 *                double *bnew
 *                boolean_T *n_too_large
 * Return Type  : void
 */
void b_float_colon_length(double a, int *n, double *anew, double *bnew,
  boolean_T *n_too_large)
{
  double ndbl;
  double absa;
  if (rtIsNaN(a)) {
    *n = 1;
    *anew = rtNaN;
    *bnew = 1.0;
    *n_too_large = false;
  } else {
    *anew = a;
    ndbl = floor(-(1.0 - a) + 0.5);
    *bnew = a + -ndbl;
    absa = fabs(a);
    if (absa >= 1.0) {
    } else {
      absa = 1.0;
    }

    if (fabs(1.0 - *bnew) < 4.4408920985006262E-16 * absa) {
      ndbl++;
      *bnew = 1.0;
    } else if (1.0 - *bnew > 0.0) {
      *bnew = a + -(ndbl - 1.0);
    } else {
      ndbl++;
    }

    *n_too_large = false;
    *n = (int)ndbl;
  }
}

/*
 * Arguments    : double b
 *                int *n
 *                double *anew
 *                double *bnew
 *                boolean_T *n_too_large
 * Return Type  : void
 */
void float_colon_length(double b, int *n, double *anew, double *bnew, boolean_T *
  n_too_large)
{
  double ndbl;
  double cdiff;
  double absb;
  if (rtIsNaN(b)) {
    *n = 1;
    *anew = rtNaN;
    *bnew = b;
    *n_too_large = false;
  } else {
    *anew = 1.0;
    ndbl = floor((b - 1.0) + 0.5);
    *bnew = 1.0 + ndbl;
    cdiff = (1.0 + ndbl) - b;
    absb = fabs(b);
    if ((1.0 >= absb) || rtIsNaN(absb)) {
      absb = 1.0;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
      ndbl++;
      *bnew = b;
    } else if (cdiff > 0.0) {
      *bnew = 1.0 + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    *n_too_large = false;
    *n = (int)ndbl;
  }
}

/*
 * File trailer for colon.c
 *
 * [EOF]
 */
