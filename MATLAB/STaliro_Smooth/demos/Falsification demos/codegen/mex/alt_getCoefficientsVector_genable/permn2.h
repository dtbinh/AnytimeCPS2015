/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * permn2.h
 *
 * Code generation for function 'permn2'
 *
 */

#ifndef __PERMN2_H__
#define __PERMN2_H__

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
#include "alt_getCoefficientsVector_genable_types.h"

/* Function Declarations */
extern void permn2(const emlrtStack *sp, emxArray_real_T *V, real_T N, real_T K,
                   emxArray_real_T *M);

#endif

/* End of code generation (permn2.h) */
