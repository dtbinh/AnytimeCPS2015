/*
 * File: evalGaussianPrecomputedInv.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

#ifndef __EVALGAUSSIANPRECOMPUTEDINV_H__
#define __EVALGAUSSIANPRECOMPUTEDINV_H__

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
extern void evalGaussianPrecomputedInv(double data[5760000], const double mu[3],
  const double invsigma[9], double g[1920000]);

#endif

/*
 * File trailer for evalGaussianPrecomputedInv.h
 *
 * [EOF]
 */
