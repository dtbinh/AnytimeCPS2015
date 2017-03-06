/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * prod.h
 *
 * Code generation for function 'prod'
 *
 */

#ifndef __PROD_H__
#define __PROD_H__

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
extern real_T prod(const emlrtStack *sp, const emxArray_real_T *x);

#ifdef __WATCOMC__

#pragma aux prod value [8087];

#endif
#endif

/* End of code generation (prod.h) */
