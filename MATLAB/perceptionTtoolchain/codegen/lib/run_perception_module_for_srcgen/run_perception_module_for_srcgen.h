/*
 * File: run_perception_module_for_srcgen.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

#ifndef __RUN_PERCEPTION_MODULE_FOR_SRCGEN_H__
#define __RUN_PERCEPTION_MODULE_FOR_SRCGEN_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "run_perception_module_for_srcgen_types.h"

/* Function Declarations */
extern void run_perception_module_for_srcgen(const unsigned char Im[5760000],
  const unsigned char colors[3], double minAcceptanceProbScalingFactor, double
  minSignificanceProb, double minAcceptanceProb, const double muPOI[12], const
  double SigmaPOI[36], const double ComponentProportionPOI[4], const double
  muNON[12], const double SigmaNON[36], const double ComponentProportionNON[4],
  const emxArray_real_T *Alpha, const emxArray_real_T *SupportVectorLabels,
  double KernelScale, const emxArray_real_T *SupportVectors, double Bias);

#endif

/*
 * File trailer for run_perception_module_for_srcgen.h
 *
 * [EOF]
 */
