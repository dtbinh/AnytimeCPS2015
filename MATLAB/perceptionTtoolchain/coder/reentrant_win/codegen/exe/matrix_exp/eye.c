/*
 * File: eye.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 02-Mar-2015 20:10:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "matrix_exp.h"
#include "eye.h"

/* Function Definitions */

/*
 * Arguments    : double I[25600]
 * Return Type  : void
 */
void eye(double I[25600])
{
  int k;
  memset(&I[0], 0, 25600U * sizeof(double));
  for (k = 0; k < 160; k++) {
    I[k + 160 * k] = 1.0;
  }
}

/*
 * File trailer for eye.c
 *
 * [EOF]
 */
