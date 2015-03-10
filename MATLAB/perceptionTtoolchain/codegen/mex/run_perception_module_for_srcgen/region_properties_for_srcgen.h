/*
 * region_properties_for_srcgen.h
 *
 * Code generation for function 'region_properties_for_srcgen'
 *
 */

#ifndef __REGION_PROPERTIES_FOR_SRCGEN_H__
#define __REGION_PROPERTIES_FOR_SRCGEN_H__

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
extern void region_properties_for_srcgen(c_run_perception_module_for_src *SD,
  const emlrtStack *sp, const real_T L[1920000], emxArray_creal_T *stats);

#endif

/* End of code generation (region_properties_for_srcgen.h) */
