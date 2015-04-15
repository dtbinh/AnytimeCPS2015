

/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
#include <solver.h>
#define ZERO_LIBRARY_MODE
Vars vars;
Params params;
Workspace work;
Settings settings;
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 6
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
void load_default_data(void) {
  
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.Q[0] = 10;
  params.Q[6] = 0;
  params.Q[12] = 0;
  params.Q[18] = 0;
  params.Q[24] = 0;
  params.Q[30] = 0;
  params.Q[1] = 0;
  params.Q[7] = 10;
  params.Q[13] = 0;
  params.Q[19] = 0;
  params.Q[25] = 0;
  params.Q[31] = 0;
  params.Q[2] = 0;
  params.Q[8] = 0;
  params.Q[14] = 10;
  params.Q[20] = 0;
  params.Q[26] = 0;
  params.Q[32] = 0;
  params.Q[3] = 0;
  params.Q[9] = 0;
  params.Q[15] = 0;
  params.Q[21] = 1;
  params.Q[27] = 0;
  params.Q[33] = 0;
  params.Q[4] = 0;
  params.Q[10] = 0;
  params.Q[16] = 0;
  params.Q[22] = 0;
  params.Q[28] = 1;
  params.Q[34] = 0;
  params.Q[5] = 0;
  params.Q[11] = 0;
  params.Q[17] = 0;
  params.Q[23] = 0;
  params.Q[29] = 0;
  params.Q[35] = 1;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.R[0] = .1;
  params.R[3] = 0;
  params.R[6] = 0;
  params.R[1] = 0;
  params.R[4] = .1;
  params.R[7] = 0;
  params.R[2] = 0;
  params.R[5] = 0;
  params.R[8] = .1;
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.Q_final[0] = 1;
  params.Q_final[6] = 0;
  params.Q_final[12] = 0;
  params.Q_final[18] = 0;
  params.Q_final[24] = 0;
  params.Q_final[30] = 0;
  params.Q_final[1] = 0;
  params.Q_final[7] = 1;
  params.Q_final[13] = 0;
  params.Q_final[19] = 0;
  params.Q_final[25] = 0;
  params.Q_final[31] = 0;
  params.Q_final[2] = 0;
  params.Q_final[8] = 0;
  params.Q_final[14] = 1;
  params.Q_final[20] = 0;
  params.Q_final[26] = 0;
  params.Q_final[32] = 0;
  params.Q_final[3] = 0;
  params.Q_final[9] = 0;
  params.Q_final[15] = 0;
  params.Q_final[21] = 1;
  params.Q_final[27] = 0;
  params.Q_final[33] = 0;
  params.Q_final[4] = 0;
  params.Q_final[10] = 0;
  params.Q_final[16] = 0;
  params.Q_final[22] = 0;
  params.Q_final[28] = 1;
  params.Q_final[34] = 0;
  params.Q_final[5] = 0;
  params.Q_final[11] = 0;
  params.Q_final[17] = 0;
  params.Q_final[23] = 0;
  params.Q_final[29] = 0;
  params.Q_final[35] = 1;
  
  params.A[0] = 1;
  params.A[1] = 0;
  params.A[2] = 0;
  params.A[3] = 0;
  params.A[4] = 0;
  params.A[5] = 0;
  params.A[6] = 0;
  params.A[7] = 1;
  params.A[8] = 0;
  params.A[9] = 0;
  params.A[10] = 0;
  params.A[11] = 0;
  params.A[12] = 0;
  params.A[13] = 0;
  params.A[14] = 1;
  params.A[15] = 0;
  params.A[16] = 0;
  params.A[17] = 0;
  params.A[18] = 0.01;
  params.A[19] = 0;
  params.A[20] = 0;
  params.A[21] = 1;
  params.A[22] = 0;
  params.A[23] = 0;
  params.A[24] = 0;
  params.A[25] = 0.01;
  params.A[26] = 0;
  params.A[27] = 0;
  params.A[28] = 1;
  params.A[29] = 0;
  params.A[30] = 0;
  params.A[31] = 0;
  params.A[32] = 0.01;
  params.A[33] = 0;
  params.A[34] = 0;
  params.A[35] = 1;
  
  params.B[0] = 0.0005;
  params.B[1] = 0;
  params.B[2] = 0;
  params.B[3] = 0.0980;
  params.B[4] = 0;
  params.B[5] = 0;
  params.B[6] = 0;
  params.B[7] = -0.0005;
  params.B[8] = 0;
  params.B[9] = 0;
  params.B[10] = -0.0980;
  params.B[11] = 0;
  params.B[12] = 0;
  params.B[13] = 0;
  params.B[14] = 0.0001;
  params.B[15] = 0;
  params.B[16] = 0;
  params.B[17] = 0.02;
  
  params.u_limit[0] = 0.052; 
  params.u_limit[1] = 0.052;
  params.u_limit[2] = 7;
  params.x_limit[0] = 100;
  params.x_limit[1] = 100;
  params.x_limit[2] = 100;
  params.x_limit[3] = 100;
  params.x_limit[4] = 100;
  params.x_limit[5] = 100;
}
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void vance_Outputs_wrapper(real_T *theta,
			real_T *phi,
			real_T *thrust,
			const real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This sample sets the output equal to the input
      y0[0] = u0[0]; 
 For complex signals use: y0[0].re = u0[0].re; 
      y0[0].im = u0[0].im;
      y1[0].re = u1[0].re;
      y1[0].im = u1[0].im;
*/

theta[0] = xD[0];
phi[0] = xD[1];
thrust[0] = xD[2];
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
  * Updates function
  *
  */
void vance_Update_wrapper(const real_T *x_hat,
			const real_T *x_ref,
			const real_T *theta,
			const real_T *phi,
			const real_T *thrust,
			real_T *xD)
{
  /* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
/*
 * Code example
 *   xD[0] = u0[0];
*/

set_defaults();
setup_indexing();
load_default_data();

params.x_0[0] = x_hat[0];
params.x_0[1] = x_hat[1];
params.x_0[2] = x_hat[2];
params.x_0[3] = x_hat[3];
params.x_0[4] = x_hat[4];
params.x_0[5] = x_hat[5];

params.x_ref[0] = x_ref[0];
params.x_ref[1] = x_ref[1];
params.x_ref[2] = x_ref[2];
params.x_ref[3] = x_ref[3];
params.x_ref[4] = x_ref[4];
params.x_ref[5] = x_ref[5];

solve();

xD[0]=vars.u_0[0];
xD[1]=vars.u_0[1];
xD[2]=vars.u_0[2];
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
