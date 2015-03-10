/*
 * mod.h
 *
 * Code generation for function 'mod'
 *
 */

#ifndef __MOD_H__
#define __MOD_H__

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
extern void b_mod(const emlrtStack *sp, const emxArray_real_T *x, real_T y,
                  emxArray_real_T *r);
extern int32_T c_mod(const emlrtStack *sp, int32_T x);

#endif

/* End of code generation (mod.h) */
