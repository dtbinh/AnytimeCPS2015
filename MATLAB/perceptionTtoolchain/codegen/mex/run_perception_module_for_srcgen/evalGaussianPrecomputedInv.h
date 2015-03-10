/*
 * evalGaussianPrecomputedInv.h
 *
 * Code generation for function 'evalGaussianPrecomputedInv'
 *
 */

#ifndef __EVALGAUSSIANPRECOMPUTEDINV_H__
#define __EVALGAUSSIANPRECOMPUTEDINV_H__

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
extern void evalGaussianPrecomputedInv(c_run_perception_module_for_src *SD,
  const emlrtStack *sp, real_T data[5760000], const real_T mu[3], const real_T
  invsigma[9], real_T g[1920000]);

#endif

/* End of code generation (evalGaussianPrecomputedInv.h) */
