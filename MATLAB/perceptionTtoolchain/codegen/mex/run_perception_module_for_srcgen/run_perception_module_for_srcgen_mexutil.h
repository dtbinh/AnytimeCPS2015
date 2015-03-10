/*
 * run_perception_module_for_srcgen_mexutil.h
 *
 * Code generation for function 'run_perception_module_for_srcgen_mexutil'
 *
 */

#ifndef __RUN_PERCEPTION_MODULE_FOR_SRCGEN_MEXUTIL_H__
#define __RUN_PERCEPTION_MODULE_FOR_SRCGEN_MEXUTIL_H__

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
extern void b_error(const emlrtStack *sp, const mxArray *b, emlrtMCInfo
                    *location);
extern const mxArray *b_message(const emlrtStack *sp, const mxArray *b,
  emlrtMCInfo *location);
extern int32_T div_s32(const emlrtStack *sp, int32_T numerator, int32_T
  denominator);
extern const mxArray *message(const emlrtStack *sp, const mxArray *b, const
  mxArray *c, emlrtMCInfo *location);

#endif

/* End of code generation (run_perception_module_for_srcgen_mexutil.h) */
