/*
 * eig.h
 *
 * Code generation for function 'eig'
 *
 */

#ifndef __EIG_H__
#define __EIG_H__

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
extern void eig(const emlrtStack *sp, const real_T A[4], creal_T V[2]);

#endif

/* End of code generation (eig.h) */
