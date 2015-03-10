/*
 * File: posteriors_for_srcgen.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

#ifndef __POSTERIORS_FOR_SRCGEN_H__
#define __POSTERIORS_FOR_SRCGEN_H__

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
extern void posteriors_for_srcgen(const double mu[12], const double Sigma[36],
  const double ComponentProportion[4], const double data[5760000], double post
  [7680000]);

#endif

/*
 * File trailer for posteriors_for_srcgen.h
 *
 * [EOF]
 */
