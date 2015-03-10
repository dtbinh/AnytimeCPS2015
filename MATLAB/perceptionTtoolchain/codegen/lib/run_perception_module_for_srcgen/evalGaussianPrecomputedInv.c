/*
 * File: evalGaussianPrecomputedInv.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "evalGaussianPrecomputedInv.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */

/*
 * Arguments    : double data[5760000]
 *                const double mu[3]
 *                const double invsigma[9]
 *                double g[1920000]
 * Return Type  : void
 */
void evalGaussianPrecomputedInv(double data[5760000], const double mu[3], const
  double invsigma[9], double g[1920000])
{
  static double b[5760000];
  int iy;
  int jA;
  int jy;
  int i3;
  int j;
  double b_data[3];
  double smax;
  double A[9];
  signed char ipiv[3];
  int c;
  int ix;
  double s;
  int ijA;
  boolean_T isodd;
  for (iy = 0; iy < 3; iy++) {
    jA = iy * 1920000;
    for (jy = 0; jy < 1920000; jy++) {
      b[jA + jy] = mu[iy];
    }
  }

  for (i3 = 0; i3 < 5760000; i3++) {
    data[i3] -= b[i3];
  }

  memset(&g[0], 0, 1920000U * sizeof(double));
  for (j = 0; j < 1920000; j++) {
    smax = 0.0;
    for (i3 = 0; i3 < 3; i3++) {
      b_data[i3] = 0.0;
      for (iy = 0; iy < 3; iy++) {
        b_data[i3] += data[j + 1920000 * iy] * invsigma[iy + 3 * i3];
      }

      smax += -0.5 * b_data[i3] * data[j + 1920000 * i3];
    }

    g[j] = exp(smax);
  }

  memcpy(&A[0], &invsigma[0], 9U * sizeof(double));
  for (i3 = 0; i3 < 3; i3++) {
    ipiv[i3] = (signed char)(1 + i3);
  }

  for (j = 0; j < 2; j++) {
    c = j << 2;
    iy = 0;
    ix = c;
    smax = fabs(A[c]);
    for (jA = 1; jA + 1 <= 3 - j; jA++) {
      ix++;
      s = fabs(A[ix]);
      if (s > smax) {
        iy = jA;
        smax = s;
      }
    }

    if (A[c + iy] != 0.0) {
      if (iy != 0) {
        ipiv[j] = (signed char)((j + iy) + 1);
        ix = j;
        iy += j;
        for (jA = 0; jA < 3; jA++) {
          smax = A[ix];
          A[ix] = A[iy];
          A[iy] = smax;
          ix += 3;
          iy += 3;
        }
      }

      i3 = (c - j) + 3;
      for (iy = c + 1; iy + 1 <= i3; iy++) {
        A[iy] /= A[c];
      }
    }

    jA = c;
    jy = c + 3;
    for (iy = 1; iy <= 2 - j; iy++) {
      smax = A[jy];
      if (A[jy] != 0.0) {
        ix = c + 1;
        i3 = (jA - j) + 6;
        for (ijA = 4 + jA; ijA + 1 <= i3; ijA++) {
          A[ijA] += A[ix] * -smax;
          ix++;
        }
      }

      jy += 3;
      jA += 3;
    }
  }

  smax = A[0];
  isodd = false;
  for (jA = 0; jA < 2; jA++) {
    smax *= A[(jA + 3 * (jA + 1)) + 1];
    if (ipiv[jA] > 1 + jA) {
      isodd = !isodd;
    }
  }

  if (isodd) {
    smax = -smax;
  }

  smax = 0.063493635934240969 * sqrt(smax);
  for (i3 = 0; i3 < 1920000; i3++) {
    g[i3] *= smax;
  }
}

/*
 * File trailer for evalGaussianPrecomputedInv.c
 *
 * [EOF]
 */
