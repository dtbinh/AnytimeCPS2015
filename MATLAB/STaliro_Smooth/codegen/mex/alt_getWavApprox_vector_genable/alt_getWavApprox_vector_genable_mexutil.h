/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * alt_getWavApprox_vector_genable_mexutil.h
 *
 * Code generation for function 'alt_getWavApprox_vector_genable_mexutil'
 *
 */

#ifndef __ALT_GETWAVAPPROX_VECTOR_GENABLE_MEXUTIL_H__
#define __ALT_GETWAVAPPROX_VECTOR_GENABLE_MEXUTIL_H__

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
extern int32_T asr_s32(int32_T u, uint32_T n);
extern emlrtCTX emlrtGetRootTLSGlobal(void);
extern void emlrtLockerFunction(EmlrtLockeeFunction aLockee, const emlrtConstCTX
  aTLS, void *aData);

#endif

/* End of code generation (alt_getWavApprox_vector_genable_mexutil.h) */
