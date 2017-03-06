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
    A = 50.26548245743669 * c_mpower(t);
    phi = (muDoubleScalarSin(2.0943951023931953 * t) + 4.0 * t / 3.0 *
           muDoubleScalarCos(12.566370614359172 * t / 3.0)) /
      (3.1415926535897931 * t - A / 9.0);
  }

  if (guard1) {
    /* phi = 2/3 + 4/(3*pi); */
    A = 3.1415926535897931 - 16.755160819145562 * b_mpower(t);
    phi = ((2.0943951023931953 * muDoubleScalarCos(2.0943951023931953 * t) +
            1.3333333333333333 * muDoubleScalarCos(4.1887902047863905 * t)) -
           5.5850536063818534 * t * muDoubleScalarSin(4.1887902047863905 * t)) /
      A;
  }

  /* evalue psi_1 */
  /* L'HopyBoy's rule at the points of 0/0 for psi_1 */
  if ((t - 0.5 == 0.0) || (t - 0.5 == 0.75) || (t - 0.5 == -0.75)) {
    b_mpower(t - 0.5);
  } else {
    c_mpower(t - 0.5);
  }

  /*  for psi_2 now */
  if ((t - 0.5 == 0.0) || (t - 0.5 == 0.375) || (t - 0.5 == -0.375)) {
    b_mpower(t - 0.5);
  } else {
    c_mpower(t - 0.5);
  }

  return phi;
}

void b_MeyerWavelet(real_T t, real_T *phi, real_T *psi)
{
  boolean_T guard1 = false;
  real_T A;
  real_T psi_1_den;
  real_T psi_1;
  real_T psi_2_den;
  real_T psi_2;

  /* % Meyer wavelet (psi) and scale (phi) as in Valenzuela and Oliviera */
  guard1 = false;
  if (t == 0.0) {
    guard1 = true;
  } else if (t == 0.75) {
    guard1 = true;
  } else if (t == -0.75) {
    guard1 = true;
  } else {
    A = 50.26548245743669 * c_mpower(t);
    *phi = (muDoubleScalarSin(2.0943951023931953 * t) + 4.0 * t / 3.0 *
            muDoubleScalarCos(12.566370614359172 * t / 3.0)) /
      (3.1415926535897931 * t - A / 9.0);
  }

  if (guard1) {
    /* phi = 2/3 + 4/(3*pi); */
    A = 3.1415926535897931 - 16.755160819145562 * b_mpower(t);
    *phi = ((2.0943951023931953 * muDoubleScalarCos(2.0943951023931953 * t) +
             1.3333333333333333 * muDoubleScalarCos(4.1887902047863905 * t)) -
            5.5850536063818534 * t * muDoubleScalarSin(4.1887902047863905 * t)) /
      A;
  }

  /* evalue psi_1 */
  /* L'HopyBoy's rule at the points of 0/0 for psi_1 */
  if ((t - 0.5 == 0.0) || (t - 0.5 == 0.75) || (t - 0.5 == -0.75)) {
    psi_1_den = 1.0 - 5.333333333333333 * b_mpower(t - 0.5);
    psi_1 = ((-0.88888888888888884 * (t - 0.5) * muDoubleScalarSin
              (2.0943951023931953 * (t - 0.5)) + 0.42441318157838759 *
              muDoubleScalarCos(2.0943951023931953 * (t - 0.5))) -
             1.3333333333333333 * muDoubleScalarCos(4.1887902047863905 * (t -
               0.5))) / psi_1_den;
  } else {
    psi_1_den = (t - 0.5) - 1.7777777777777777 * c_mpower(t - 0.5);
    psi_1 = (0.42441318157838759 * (t - 0.5) * muDoubleScalarCos
             (2.0943951023931953 * (t - 0.5)) - 0.31830988618379069 *
             muDoubleScalarSin(4.1887902047863905 * (t - 0.5))) / psi_1_den;
  }

  /*  for psi_2 now */
  if ((t - 0.5 == 0.0) || (t - 0.5 == 0.375) || (t - 0.5 == -0.375)) {
    psi_2_den = 1.0 - 21.333333333333332 * b_mpower(t - 0.5);
    psi_2 = ((-7.1111111111111107 * (t - 0.5) * muDoubleScalarSin
              (8.3775804095727811 * (t - 0.5)) + 0.84882636315677518 *
              muDoubleScalarCos(8.3775804095727811 * (t - 0.5))) +
             1.3333333333333333 * muDoubleScalarCos(4.1887902047863905 * (t -
               0.5))) / psi_2_den;
  } else {
    psi_2_den = (t - 0.5) - 7.1111111111111107 * c_mpower(t - 0.5);
    psi_2 = (0.84882636315677518 * (t - 0.5) * muDoubleScalarCos
             (8.3775804095727811 * (t - 0.5)) + 0.31830988618379069 *
             muDoubleScalarSin(4.1887902047863905 * (t - 0.5))) / psi_2_den;
  }

  *psi = psi_1 + psi_2;
}

/* End of code generation (MeyerWavelet.c) */
