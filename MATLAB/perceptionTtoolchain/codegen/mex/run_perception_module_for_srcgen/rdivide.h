/*
 * rdivide.h
 *
 * Code generation for function 'rdivide'
 *
 */

#ifndef __RDIVIDE_H__
#define __RDIVIDE_H__

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
extern void b_rdivide(const real_T x[7680000], const real_T y[7680000], real_T
                      z[7680000]);
extern void c_rdivide(const real_T x[2], real_T y, real_T z[2]);
extern void rdivide(const real_T x[5760000], const real_T y[5760000], real_T z
                    [5760000]);

#endif

/* End of code generation (rdivide.h) */
