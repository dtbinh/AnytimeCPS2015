/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * alt_getCoefficientsVector_genable.h
 *
 * Code generation for function 'alt_getCoefficientsVector_genable'
 *
 */

#ifndef __ALT_GETCOEFFICIENTSVECTOR_GENABLE_H__
#define __ALT_GETCOEFFICIENTSVECTOR_GENABLE_H__

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "blas.h"
#include "rtwtypes.h"
#include "alt_getCoefficientsVector_genable_types.h"

/* Function Declarations */
extern void alt_getCoefficientsVector_genable(const emlrtStack *sp, const real_T
  grid_x[81], const real_T dist_array_xy[6561], real_T dx, real_T j_min, real_T
  j_max, real_T k_min, real_T k_max, const real_T E_dash[8], real_T viz,
  emxArray_real_T *C_00k, emxArray_real_T *D_ejk);

#endif

/* End of code generation (alt_getCoefficientsVector_genable.h) */
