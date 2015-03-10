/*
 * File: sum.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

#ifndef __SUM_H__
#define __SUM_H__

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
extern void b_sum(const double x[7680000], double y[1920000]);
extern void c_sum(const emxArray_real_T *x, double y[2]);
extern void sum(const double x[5760000], double y[1920000]);

#endif

/*
 * File trailer for sum.h
 *
 * [EOF]
 */
