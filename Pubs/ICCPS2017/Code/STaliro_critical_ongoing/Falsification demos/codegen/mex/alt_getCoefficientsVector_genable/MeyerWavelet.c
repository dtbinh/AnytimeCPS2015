/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * MeyerWavelet.c
 *
 * Code generation for function 'MeyerWavelet'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "alt_getCoefficientsVector_genable.h"
#include "MeyerWavelet.h"
#include "mpower.h"

/* Function Definitions */
real_T MeyerWavelet(real_T t)
{
  real_T phi;
  boolean_T guard1 = false;
  real_T A;

  /* % Meyer wavelet (psi) and scale (phi) as in Valenzuela and Oliviera */
  guard1 = false;
  if (t == 0.0) {
    guard1 = true;
  } else if (t == 0.75) {
    guard1 = true;
  } else if (t == -0.75) {
    guard1 = true;
  } else {
    A = 50.26548245743669 * b_mpower(t);
    phi = (muDoubleScalarSin(2.0943951023931953 * t) + 4.0 * t / 3.0 *
           muDoubleScalarCos(12.566370614359172 * t / 3.0)) /
      (3.1415926535897931 * t - A / 9.0);
  }

  if (guard1) {
    /* phi = 2/3 + 4/(3*pi); */
    A = 3.1415926535897931 - 16.755160819145562 * mpower(t);
    phi = ((2.0943951023931953 * muDoubleScalarCos(2.0943951023931953 * t) +
            1.3333333333333333 * muDoubleScalarCos(4.1887902047863905 * t)) -
           5.5850536063818534 * t * muDoubleScalarSin(4.1887902047863905 * t)) /
      A;
  }

  /* evalue psi_1 */
  /* L'HopyBoy's rule at the points of 0/0 for psi_1 */
  if ((t - 0.5 == 0.0) || (t - 0.5 == 0.75) || (t - 0.5 == -0.75)) {
    mpower(t - 0.5);
  } else {
    b_mpower(t - 0.5);
  }

  /*  for psi_2 now */
  if ((t - 0.5 == 0.0) || (t - 0.5 == 0.375) || (t - 0.5 == -0.375)) {
    mpower(t - 0.5);
  } else {
    b_mpower(t - 0.5);
  }

  return phi;
}

/* End of code generation (MeyerWavelet.c) */
