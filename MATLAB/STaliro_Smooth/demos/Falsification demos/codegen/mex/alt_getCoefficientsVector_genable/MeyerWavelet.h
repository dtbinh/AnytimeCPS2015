/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * MeyerWavelet.h
 *
 * Code generation for function 'MeyerWavelet'
 *
 */

#ifndef __MEYERWAVELET_H__
#define __MEYERWAVELET_H__

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
extern real_T MeyerWavelet(real_T t);

#ifdef __WATCOMC__

#pragma aux MeyerWavelet value [8087];

#endif

extern void b_MeyerWavelet(real_T t, real_T *phi, real_T *psi);

#endif

/* End of code generation (MeyerWavelet.h) */
