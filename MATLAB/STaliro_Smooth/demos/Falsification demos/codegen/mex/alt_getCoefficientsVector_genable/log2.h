/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * log2.h
 *
 * Code generation for function 'log2'
 *
 */

#ifndef __LOG2_H__
#define __LOG2_H__

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
extern real_T b_log2(real_T x);

#ifdef __WATCOMC__

#pragma aux b_log2 value [8087];

#endif
#endif

/* End of code generation (log2.h) */
