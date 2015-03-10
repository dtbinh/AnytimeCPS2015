/*
 * File: matrix_exp.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 02-Mar-2015 20:10:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "matrix_exp.h"
#include "norm.h"
#include "eye.h"

/* Function Definitions */

/*
 * The function matrix_exp computes matrix exponential of
 *  the input matrix using Taylor series and returns the
 *  computed output.
 * Arguments    : matrix_expStackData *SD
 *                const double X[25600]
 *                double Y[25600]
 * Return Type  : void
 */
void matrix_exp(matrix_expStackData *SD, const double X[25600], double Y[25600])
{
  double k;
  int32_T exitg1;
  int i0;
  int i1;
  double d0;
  int i2;
  memset(&Y[0], 0, 25600U * sizeof(double));
  eye(SD->f0.F);
  k = 1.0;
  do {
    exitg1 = 0;
    for (i0 = 0; i0 < 25600; i0++) {
      SD->f0.Y[i0] = (Y[i0] + SD->f0.F[i0]) - Y[i0];
    }

    if (norm(SD->f0.Y) > 0.0) {
      for (i0 = 0; i0 < 25600; i0++) {
        Y[i0] += SD->f0.F[i0];
      }

      for (i0 = 0; i0 < 160; i0++) {
        for (i1 = 0; i1 < 160; i1++) {
          d0 = 0.0;
          for (i2 = 0; i2 < 160; i2++) {
            d0 += X[i0 + 160 * i2] * SD->f0.F[i2 + 160 * i1];
          }

          SD->f0.X[i0 + 160 * i1] = d0 / k;
        }
      }

      for (i0 = 0; i0 < 160; i0++) {
        memcpy(&SD->f0.F[160 * i0], &SD->f0.X[160 * i0], 160U * sizeof(double));
      }

      k++;
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/*
 * File trailer for matrix_exp.c
 *
 * [EOF]
 */
