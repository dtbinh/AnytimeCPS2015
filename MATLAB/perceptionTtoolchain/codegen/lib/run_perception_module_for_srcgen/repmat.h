/*
 * File: repmat.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

#ifndef __REPMAT_H__
#define __REPMAT_H__

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
extern void b_repmat(const double a[1920000], double b[5760000]);
extern void c_repmat(const double a[4], double b[7680000]);
extern void d_repmat(const double a[1920000], double b[7680000]);
extern void e_repmat(const double a[2], double varargin_1, emxArray_real_T *b);
extern void repmat(const boolean_T a[1920000], boolean_T b[5760000]);

#endif

/*
 * File trailer for repmat.h
 *
 * [EOF]
 */
