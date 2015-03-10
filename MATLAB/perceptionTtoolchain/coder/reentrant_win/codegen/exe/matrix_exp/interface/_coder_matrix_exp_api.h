/* 
 * File: _coder_matrix_exp_api.h 
 *  
 * MATLAB Coder version            : 2.7 
 * C/C++ source code generated on  : 02-Mar-2015 20:10:32 
 */

#ifndef ___CODER_MATRIX_EXP_API_H__
#define ___CODER_MATRIX_EXP_API_H__
/* Include Files */ 
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Function Declarations */ 
extern void matrix_exp_initialize(emlrtContext *aContext);
extern void matrix_exp_terminate(void);
extern void matrix_exp_atexit(void);
extern void matrix_exp_api(const mxArray *prhs[1], const mxArray *plhs[1]);
extern void matrix_exp(real_T X[25600], real_T Y[25600]);
extern void matrix_exp_xil_terminate(void);

#endif
/* 
 * File trailer for _coder_matrix_exp_api.h 
 *  
 * [EOF] 
 */
