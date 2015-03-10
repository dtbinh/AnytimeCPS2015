/* 
 * File: _coder_polar2cartesian_api.h 
 *  
 * MATLAB Coder version            : 2.7 
 * C/C++ source code generated on  : 02-Mar-2015 20:01:11 
 */

#ifndef ___CODER_POLAR2CARTESIAN_API_H__
#define ___CODER_POLAR2CARTESIAN_API_H__
/* Include Files */ 
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Function Declarations */ 
extern void polar2cartesian_initialize(emlrtContext *aContext);
extern void polar2cartesian_terminate(void);
extern void polar2cartesian_atexit(void);
extern void polar2cartesian_api(const mxArray * const prhs[2], const mxArray *plhs[2]);
extern void polar2cartesian(real_T r, real_T theta, real_T *x, real_T *y);
extern void polar2cartesian_xil_terminate(void);

#endif
/* 
 * File trailer for _coder_polar2cartesian_api.h 
 *  
 * [EOF] 
 */
