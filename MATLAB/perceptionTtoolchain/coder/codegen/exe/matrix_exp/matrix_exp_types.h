/* 
 * File: matrix_exp_types.h 
 *  
 * MATLAB Coder version            : 2.7 
 * C/C++ source code generated on  : 02-Mar-2015 20:10:22 
 */

#ifndef __MATRIX_EXP_TYPES_H__
#define __MATRIX_EXP_TYPES_H__

/* Include Files */ 
#include "rtwtypes.h"

/* Type Definitions */ 
#ifndef typedef_matrix_expStackData
#define typedef_matrix_expStackData
typedef struct
{
    struct
    {
        double F[25600];
        double Y[25600];
        double X[25600];
    } f0;
} matrix_expStackData;
#endif /*typedef_matrix_expStackData*/

#endif
/* 
 * File trailer for matrix_exp_types.h 
 *  
 * [EOF] 
 */
