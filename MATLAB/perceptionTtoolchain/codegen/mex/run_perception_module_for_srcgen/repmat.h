/*
 * repmat.h
 *
 * Code generation for function 'repmat'
 *
 */

#ifndef __REPMAT_H__
#define __REPMAT_H__

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
extern void b_repmat(const real_T a[1920000], real_T b[5760000]);
extern void c_repmat(const real_T a[4], real_T b[7680000]);
extern void d_repmat(const real_T a[1920000], real_T b[7680000]);
extern void e_repmat(const emlrtStack *sp, const real_T a[2], real_T varargin_1,
                     emxArray_real_T *b);
extern void repmat(const boolean_T a[1920000], boolean_T b[5760000]);

#endif

/* End of code generation (repmat.h) */
