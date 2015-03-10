/*
 * run_perception_module_for_srcgen_types.h
 *
 * Code generation for function 'run_perception_module_for_srcgen'
 *
 */

#ifndef __RUN_PERCEPTION_MODULE_FOR_SRCGEN_TYPES_H__
#define __RUN_PERCEPTION_MODULE_FOR_SRCGEN_TYPES_H__

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_c_run_perception_module_for_src
#define typedef_c_run_perception_module_for_src
typedef struct
{
    union
    {
        struct
        {
            boolean_T x[1920000];
        } f0;
        struct
        {
            real_T b[5760000];
        } f1;
    } u1;
    struct
    {
        real_T likelihood[7680000];
        real_T dv3[7680000];
        real_T b_likelihood[7680000];
        real_T dv4[7680000];
        real_T data[5760000];
        real_T den[1920000];
    } f2;
    struct
    {
        real_T posteriorspoi[7680000];
        real_T posteriorsnon[7680000];
        real_T dv2[7680000];
        real_T b_posteriorspoi[7680000];
        real_T I[5760000];
        real_T dv0[5760000];
        real_T dv1[5760000];
        real_T b_I[5760000];
        real_T candidate[5760000];
        real_T s[1920000];
        real_T d2[1920000];
        boolean_T S[5760000];
        boolean_T B[1920000];
        boolean_T b_s[1920000];
        boolean_T M[1920000];
        boolean_T clusterObjOfInterest[1920000];
    } f3;
} c_run_perception_module_for_src;
#endif /*typedef_c_run_perception_module_for_src*/
#ifndef struct_emxArray__common
#define struct_emxArray__common
struct emxArray__common
{
    void *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray__common*/
#ifndef typedef_emxArray__common
#define typedef_emxArray__common
typedef struct emxArray__common emxArray__common;
#endif /*typedef_emxArray__common*/
#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T
struct emxArray_boolean_T
{
    boolean_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_boolean_T*/
#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T
typedef struct emxArray_boolean_T emxArray_boolean_T;
#endif /*typedef_emxArray_boolean_T*/
#ifndef struct_emxArray_creal_T
#define struct_emxArray_creal_T
struct emxArray_creal_T
{
    creal_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_creal_T*/
#ifndef typedef_emxArray_creal_T
#define typedef_emxArray_creal_T
typedef struct emxArray_creal_T emxArray_creal_T;
#endif /*typedef_emxArray_creal_T*/
#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T
struct emxArray_int32_T
{
    int32_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_int32_T*/
#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T
typedef struct emxArray_int32_T emxArray_int32_T;
#endif /*typedef_emxArray_int32_T*/
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
#ifndef struct_emxArray_real_T_1x1600
#define struct_emxArray_real_T_1x1600
struct emxArray_real_T_1x1600
{
    real_T data[1600];
    int32_T size[2];
};
#endif /*struct_emxArray_real_T_1x1600*/
#ifndef typedef_emxArray_real_T_1x1600
#define typedef_emxArray_real_T_1x1600
typedef struct emxArray_real_T_1x1600 emxArray_real_T_1x1600;
#endif /*typedef_emxArray_real_T_1x1600*/
#ifndef struct_emxArray_real_T_4x2
#define struct_emxArray_real_T_4x2
struct emxArray_real_T_4x2
{
    real_T data[8];
    int32_T size[2];
};
#endif /*struct_emxArray_real_T_4x2*/
#ifndef typedef_emxArray_real_T_4x2
#define typedef_emxArray_real_T_4x2
typedef struct emxArray_real_T_4x2 emxArray_real_T_4x2;
#endif /*typedef_emxArray_real_T_4x2*/
#ifndef struct_emxArray_uint32_T
#define struct_emxArray_uint32_T
struct emxArray_uint32_T
{
    uint32_T *data;
    int32_T *size;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
};
#endif /*struct_emxArray_uint32_T*/
#ifndef typedef_emxArray_uint32_T
#define typedef_emxArray_uint32_T
typedef struct emxArray_uint32_T emxArray_uint32_T;
#endif /*typedef_emxArray_uint32_T*/

#endif
/* End of code generation (run_perception_module_for_srcgen_types.h) */
