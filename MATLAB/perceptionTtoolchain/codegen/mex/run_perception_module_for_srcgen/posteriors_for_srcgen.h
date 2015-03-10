/*
 * posteriors_for_srcgen.h
 *
 * Code generation for function 'posteriors_for_srcgen'
 *
 */

#ifndef __POSTERIORS_FOR_SRCGEN_H__
#define __POSTERIORS_FOR_SRCGEN_H__

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
extern void posteriors_for_srcgen(c_run_perception_module_for_src *SD, const
  emlrtStack *sp, const real_T mu[12], const real_T Sigma[36], const real_T
  ComponentProportion[4], const real_T data[5760000], real_T post[7680000]);

#endif

/* End of code generation (posteriors_for_srcgen.h) */
