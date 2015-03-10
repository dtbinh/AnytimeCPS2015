/*
 * run_perception_module_for_srcgen.h
 *
 * Code generation for function 'run_perception_module_for_srcgen'
 *
 */

#ifndef __RUN_PERCEPTION_MODULE_FOR_SRCGEN_H__
#define __RUN_PERCEPTION_MODULE_FOR_SRCGEN_H__

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
extern void run_perception_module_for_srcgen(c_run_perception_module_for_src *SD,
  const emlrtStack *sp, const uint8_T Im[5760000], const uint8_T colors[3],
  real_T minAcceptanceProbScalingFactor, real_T minSignificanceProb, real_T
  minAcceptanceProb, const real_T muPOI[12], const real_T SigmaPOI[36], const
  real_T ComponentProportionPOI[4], const real_T muNON[12], const real_T
  SigmaNON[36], const real_T ComponentProportionNON[4], const emxArray_real_T
  *Alpha, const emxArray_real_T *SupportVectorLabels, real_T KernelScale, const
  emxArray_real_T *SupportVectors, real_T Bias);

#endif

/* End of code generation (run_perception_module_for_srcgen.h) */
