/*
 * colon.h
 *
 * Code generation for function 'colon'
 *
 */

#ifndef __COLON_H__
#define __COLON_H__

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
extern void assert_pmaxsize(const emlrtStack *sp, boolean_T p);
extern void b_float_colon_length(real_T a, int32_T *n, real_T *anew, real_T
  *bnew, boolean_T *n_too_large);
extern void float_colon_length(real_T b, int32_T *n, real_T *anew, real_T *bnew,
  boolean_T *n_too_large);

#endif

/* End of code generation (colon.h) */
