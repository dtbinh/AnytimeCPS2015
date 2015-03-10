/*
 * sum.h
 *
 * Code generation for function 'sum'
 *
 */

#ifndef __SUM_H__
#define __SUM_H__

/* Include files */
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "blas.h"
#include "rtwtypes.h"
#include "run_perception_module_for_srcgen_types.h"

/* Function Declarations */
extern void b_sum(const real_T x[7680000], real_T y[1920000]);
extern void c_sum(const emlrtStack *sp, const emxArray_real_T *x, real_T y[2]);
extern void sum(const real_T x[5760000], real_T y[1920000]);

#endif

/* End of code generation (sum.h) */
