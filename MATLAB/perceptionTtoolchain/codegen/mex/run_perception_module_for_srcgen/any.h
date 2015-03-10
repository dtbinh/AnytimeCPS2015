/*
 * any.h
 *
 * Code generation for function 'any'
 *
 */

#ifndef __ANY_H__
#define __ANY_H__

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
extern void any(const emlrtStack *sp, const boolean_T x[5760000], boolean_T y
                [1920000]);
extern void b_any(const emlrtStack *sp, const boolean_T x[1920000], boolean_T y
                  [1200]);
extern boolean_T c_any(const boolean_T x[1200]);

#endif

/* End of code generation (any.h) */
