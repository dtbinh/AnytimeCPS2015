/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * alt_getWavApprox_vector_genable.h
 *
 * Code generation for function 'alt_getWavApprox_vector_genable'
 *
 */

#ifndef __ALT_GETWAVAPPROX_VECTOR_GENABLE_H__
#define __ALT_GETWAVAPPROX_VECTOR_GENABLE_H__

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
#include "omp.h"
#include "alt_getWavApprox_vector_genable_types.h"

/* Function Declarations */
extern real_T alt_getWavApprox_vector_genable(const emlrtStack *sp, const
  emxArray_real_T *x, const emxArray_real_T *C_00k, const emxArray_real_T *D_ejk,
  real_T k_min, real_T k_max, real_T j_min, real_T j_max, const emxArray_real_T *
  E_dash);

#ifdef __WATCOMC__

#pragma aux alt_getWavApprox_vector_genable value [8087];

#endif
#endif

/* End of code generation (alt_getWavApprox_vector_genable.h) */
