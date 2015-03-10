/* 
 * File: _coder_run_perception_module_for_srcgen_api.h 
 *  
 * MATLAB Coder version            : 2.7 
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01 
 */

#ifndef ___CODER_RUN_PERCEPTION_MODULE_FOR_SRCGEN_API_H__
#define ___CODER_RUN_PERCEPTION_MODULE_FOR_SRCGEN_API_H__
/* Include Files */ 
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Type Definitions */ 
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T
{
    real_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_real_T*/
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /*typedef_emxArray_real_T*/

/* Function Declarations */ 
extern void run_perception_module_for_srcgen_initialize(emlrtContext *aContext);
extern void run_perception_module_for_srcgen_terminate(void);
extern void run_perception_module_for_srcgen_atexit(void);
extern void run_perception_module_for_srcgen_api(const mxArray *prhs[16]);
extern void run_perception_module_for_srcgen(uint8_T Im[5760000], uint8_T colors[3], real_T minAcceptanceProbScalingFactor, real_T minSignificanceProb, real_T minAcceptanceProb, real_T muPOI[12], real_T SigmaPOI[36], real_T ComponentProportionPOI[4], real_T muNON[12], real_T SigmaNON[36], real_T ComponentProportionNON[4], emxArray_real_T *Alpha, emxArray_real_T *SupportVectorLabels, real_T KernelScale, emxArray_real_T *SupportVectors, real_T Bias);
extern void run_perception_module_for_srcgen_xil_terminate(void);

#endif
/* 
 * File trailer for _coder_run_perception_module_for_srcgen_api.h 
 *  
 * [EOF] 
 */
