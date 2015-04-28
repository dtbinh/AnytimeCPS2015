#include <rmpc_control/rmpcControl.hpp>
#include <iostream>
#include <rmpc_control/solver.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ros/console.h>
#include <vector>
//#include "ldl.c"
//#include "matrix_support.c"
//#include "solver.c"
//#include "util.c"
//#include "cowsay.c"
//#include <ros/ros.h>

Vars vars;
Params params;
Workspace work;
Settings settings;


rmpcControl::rmpcControl()
  : mass_(0.5),
    g_(9.81),
    yaw_int_(0.0),
    max_pos_int_(0.5)
{
}

void rmpcControl::setMass(const float mass)
{
  mass_ = mass;
}

void rmpcControl::setGravity(const float g)
{
  g_ = g;
}

void rmpcControl::setPosition(const Eigen::Vector3f &position)
{
  pos_ = position;
}

void rmpcControl::setVelocity(const Eigen::Vector3f &velocity)
{
  vel_ = velocity;
}

void rmpcControl::setYaw(const float current_yaw)
{
  current_yaw_ = current_yaw;
}

void rmpcControl::setMaxIntegral(const float max_integral)
{
  max_pos_int_ = max_integral;
}

void rmpcControl::setOptParams( std::vector<double> A,
                               std::vector<double> B,
			       std::vector<double> x_limit,
			       std::vector<double> u_limit)
			       
{ // use this function to get params through the parameter server
 set_defaults();
 setup_indexing();
 load_default_data();
/* ignore these guys for RMPC for now, no other choice son 
 params.A[0] = A[0];
 params.A[1] = A[1];
 params.A[2] = A[2];
 params.A[3] = A[3];
 params.A[4] = A[4];
 params.A[5] = A[5]; 
 params.A[6] = A[6];
 params.A[7] = A[7];
 params.A[8] = A[8];
 
 params.B[0] = B[0];
 params.B[1] = B[1];
 params.B[2] = B[2];
 params.B[3] = B[3];
 params.B[4] = B[4];
 params.B[5] = B[5]; 

 params.x_limit[0] = x_limit[0];
 params.x_limit[1] = x_limit[1];
 params.x_limit[2] = x_limit[2];
 params.x_limit[3] = x_limit[3];
 params.x_limit[4] = x_limit[4];
 params.x_limit[5] = x_limit[5];
*/ 
 params.u_limit[0] = u_limit[0];
 params.u_limit[1] = u_limit[1];
 params.u_limit[2] = u_limit[2]; 




}

void rmpcControl::calculateControl(const Eigen::Vector3f &des_pos,
                                  const Eigen::Vector3f &des_vel,
                                  const Eigen::Vector3f &des_acc,
                                  const float des_yaw,
                                  const Eigen::Vector3f &kx,
                                  const Eigen::Vector3f &kv,
                                  const Eigen::Vector3f &ki,
                                  const float ki_yaw)
{
  Eigen::Vector3f e_pos = (des_pos - pos_);
  Eigen::Vector3f e_vel = (des_vel - vel_);
  for(int i = 0; i < 3; i++)
  {
    if(kx(i) != 0)
      pos_int_(i) += ki(i)*e_pos(i);

    // Limit integral term
    if(pos_int_(i) > max_pos_int_)
      pos_int_(i) = max_pos_int_;
    else if(pos_int_(i) < -max_pos_int_)
      pos_int_(i) = -max_pos_int_;
  }
 //std::cout<<params.A[0]<<" "<<params.A[1]<<std::endl;
  
 
 params.z_ref[0] = des_pos[0];
 params.z_ref[1] = des_pos[1];
 params.z_ref[2] = des_pos[2];
 params.z_ref[3] = des_vel[0];
 params.z_ref[4] = des_vel[1];
 params.z_ref[5] = des_vel[2];

 params.z_ref[6] = 0; // for the controls
 params.z_ref[7] = 0;
 params.z_ref[8] = 0;

 params.z_0[0] = pos_[0];
 params.z_0[1] = pos_[1];
 params.z_0[2] = pos_[2];
 params.z_0[3] = vel_[0];
 params.z_0[4] = vel_[1];
 params.z_0[5] = vel_[2];
 
 params.z_0[6] = 0; // find a way to get previous trp in here
 params.z_0[7] = 0;
 params.z_0[8] = 0;


 solve();
 
 trpy_(0) = vars.u_0[2] + mass_*g_; //thrust
 trpy_(1) = vars.u_0[1]; //roll
 trpy_(2) = vars.u_0[0]; //pitch
 trpy_(3) = 0; //yaw
 
/* if(0)
 {
char **dummy = (char**) malloc(2 * sizeof(char*));
dummy[1] = (char*) malloc(6 * sizeof(char));
strcpy(dummy[1], "VaNcE");
 cowsay(2, dummy);
 free(dummy[1]);
 free(dummy);
}*/

}
const Eigen::Vector4f &rmpcControl::getControls(void)
{ 
 // ros::Duration(.038).sleep(); //add delay
  return trpy_;
}

void rmpcControl::resetIntegrals(void)
{
  pos_int_ = Eigen::Vector3f::Zero();
  yaw_int_ = 0;
}

void load_default_data(void) {
 
   
 /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.Q[0] = 10;
  params.Q[9] = 0;
  params.Q[18] = 0;
  params.Q[27] = 0;
  params.Q[36] = 0;
  params.Q[45] = 0;
  params.Q[54] = 0;
  params.Q[63] = 0;
  params.Q[72] = 0;
  params.Q[1] = 0;
  params.Q[10] = 10;
  params.Q[19] = 0;
  params.Q[28] = 0;
  params.Q[37] = 0;
  params.Q[46] = 0;
  params.Q[55] = 0;
  params.Q[64] = 0;
  params.Q[73] = 0;
  params.Q[2] = 0;
  params.Q[11] = 0;
  params.Q[20] = 10;
  params.Q[29] = 0;
  params.Q[38] = 0;
  params.Q[47] = 0;
  params.Q[56] = 0;
  params.Q[65] = 0;
  params.Q[74] = 0;
  params.Q[3] = 0;
  params.Q[12] = 0;
  params.Q[21] = 0;
  params.Q[30] = 1;
  params.Q[39] = 0;
  params.Q[48] = 0;
  params.Q[57] = 0;
  params.Q[66] = 0;
  params.Q[75] = 0;
  params.Q[4] = 0;
  params.Q[13] = 0;
  params.Q[22] = 0;
  params.Q[31] = 0;
  params.Q[40] = 1;
  params.Q[49] = 0;
  params.Q[58] = 0;
  params.Q[67] = 0;
  params.Q[76] = 0;
  params.Q[5] = 0;
  params.Q[14] = 0;
  params.Q[23] = 0;
  params.Q[32] = 0;
  params.Q[41] = 0;
  params.Q[50] = 1;
  params.Q[59] = 0;
  params.Q[68] = 0;
  params.Q[77] = 0;
  params.Q[6] = 0;
  params.Q[15] = 0;
  params.Q[24] = 0;
  params.Q[33] = 0;
  params.Q[42] = 0;
  params.Q[51] = 0;
  params.Q[60] = 10;
  params.Q[69] = 0;
  params.Q[78] = 0;
  params.Q[7] = 0;
  params.Q[16] = 0;
  params.Q[25] = 0;
  params.Q[34] = 0;
  params.Q[43] = 0;
  params.Q[52] = 0;
  params.Q[61] = 0;
  params.Q[70] = 10;
  params.Q[79] = 0;
  params.Q[8] = 0;
  params.Q[17] = 0;
  params.Q[26] = 0;
  params.Q[35] = 0;
  params.Q[44] = 0;
  params.Q[53] = 0;
  params.Q[62] = 0;
  params.Q[71] = 0;
  params.Q[80] = .1; 
  
  
  
  /* Make this a diagonal PSD matrix, even though it's not diagonal. */
  params.Q_final[0] = 10;
  params.Q_final[9] = 0;
  params.Q_final[18] = 0;
  params.Q_final[27] = 0;
  params.Q_final[36] = 0;
  params.Q_final[45] = 0;
  params.Q_final[54] = 0;
  params.Q_final[63] = 0;
  params.Q_final[72] = 0;
  params.Q_final[1] = 0;
  params.Q_final[10] = 10;
  params.Q_final[19] = 0;
  params.Q_final[28] = 0;
  params.Q_final[37] = 0;
  params.Q_final[46] = 0;
  params.Q_final[55] = 0;
  params.Q_final[64] = 0;
  params.Q_final[73] = 0;
  params.Q_final[2] = 0;
  params.Q_final[11] = 0;
  params.Q_final[20] = 10;
  params.Q_final[29] = 0;
  params.Q_final[38] = 0;
  params.Q_final[47] = 0;
  params.Q_final[56] = 0;
  params.Q_final[65] = 0;
  params.Q_final[74] = 0;
  params.Q_final[3] = 0;
  params.Q_final[12] = 0;
  params.Q_final[21] = 0;
  params.Q_final[30] = 1;
  params.Q_final[39] = 0;
  params.Q_final[48] = 0;
  params.Q_final[57] = 0;
  params.Q_final[66] = 0;
  params.Q_final[75] = 0;
  params.Q_final[4] = 0;
  params.Q_final[13] = 0;
  params.Q_final[22] = 0;
  params.Q_final[31] = 0;
  params.Q_final[40] = 1;
  params.Q_final[49] = 0;
  params.Q_final[58] = 0;
  params.Q_final[67] = 0;
  params.Q_final[76] = 0;
  params.Q_final[5] = 0;
  params.Q_final[14] = 0;
  params.Q_final[23] = 0;
  params.Q_final[32] = 0;
  params.Q_final[41] = 0;
  params.Q_final[50] = 1;
  params.Q_final[59] = 0;
  params.Q_final[68] = 0;
  params.Q_final[77] = 0;
  params.Q_final[6] = 0;
  params.Q_final[15] = 0;
  params.Q_final[24] = 0;
  params.Q_final[33] = 0;
  params.Q_final[42] = 0;
  params.Q_final[51] = 0;
  params.Q_final[60] = 10;
  params.Q_final[69] = 0;
  params.Q_final[78] = 0;
  params.Q_final[7] = 0;
  params.Q_final[16] = 0;
  params.Q_final[25] = 0;
  params.Q_final[34] = 0;
  params.Q_final[43] = 0;
  params.Q_final[52] = 0;
  params.Q_final[61] = 0;
  params.Q_final[70] = 10;
  params.Q_final[79] = 0;
  params.Q_final[8] = 0;
  params.Q_final[17] = 0;
  params.Q_final[26] = 0;
  params.Q_final[35] = 0;
  params.Q_final[44] = 0;
  params.Q_final[53] = 0;
  params.Q_final[62] = 0;
  params.Q_final[71] = 0;
  params.Q_final[80] = .1;
 
  params.u_limit[0] = 0.012; // 0.0052 works
  params.u_limit[1] = 0.012;
  params.u_limit[2] = 7;
  
  params.A_0[0] = 1;
  params.A_0[1] = 0.05;
  params.A_0[2] = 0.0115;
  params.A_0[3] = 1;
  params.A_0[4] = 0.05;
  params.A_0[5] = -0.0115;
  params.A_0[6] = 1;
  params.A_0[7] = 0.05;
  params.A_0[8] = 0.0024;
  params.A_0[9] = 1;
  params.A_0[10] = 0.3724;
  params.A_0[11] = 1;
  params.A_0[12] = -0.3724;
  params.A_0[13] = 1;
  params.A_0[14] = 0.076;
  
  params.B_0[0] = 0.0007;
  params.B_0[1] = -0.0007;
  params.B_0[2] = 0.0001;
  params.B_0[3] = 0.1176;
  params.B_0[4] = -0.1176;
  params.B_0[5] = 0.024;
  params.B_0[6] = 1;
  params.B_0[7] = 1;
  params.B_0[8] = 1;
  
  params.A[0] = 1;
  params.A[1] = 0.05;
  params.A[2] = 0.0115;
  params.A[3] = 1;
  params.A[4] = 0.05;
  params.A[5] = -0.0115;
  params.A[6] = 1;
  params.A[7] = 0.05;
  params.A[8] = 0.0024;
  params.A[9] = 1;
  params.A[10] = 0.3724;
  params.A[11] = 1;
  params.A[12] = -0.3724;
  params.A[13] = 1;
  params.A[14] = 0.076;  

  params.B[0] = 0.0007;
  params.B[1] = -0.0007;
  params.B[2] = 0.0001;
  params.B[3] = 0.1176;
  params.B[4] = -0.1176;
  params.B[5] = 0.024;
  params.B[6] = 1;
  params.B[7] = 1;
  params.B[8] = 1;



}



 
