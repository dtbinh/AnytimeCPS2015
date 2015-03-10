/* 
 * File: _coder_test_code_style_api.h 
 *  
 * MATLAB Coder version            : 2.7 
 * C/C++ source code generated on  : 02-Mar-2015 19:56:54 
 */

#ifndef ___CODER_TEST_CODE_STYLE_API_H__
#define ___CODER_TEST_CODE_STYLE_API_H__
/* Include Files */ 
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Function Declarations */ 
extern void test_code_style_initialize(emlrtContext *aContext);
extern void test_code_style_terminate(void);
extern void test_code_style_atexit(void);
extern void test_code_style_api(const mxArray * const prhs[1], const mxArray *plhs[1]);
extern real_T test_code_style(int16_T x);
extern void test_code_style_xil_terminate(void);

#endif
/* 
 * File trailer for _coder_test_code_style_api.h 
 *  
 * [EOF] 
 */
