/*
 * inv.h
 *
 * Code generation for function 'inv'
 *
 */

#ifndef __INV_H__
#define __INV_H__

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
extern void inv(const emlrtStack *sp, const real_T x[9], real_T y[9]);

#endif

/* End of code generation (inv.h) */
