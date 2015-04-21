#include <mpc_control/mpcControl.hpp>
#include <iostream>
#include <mpc_control/solver.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ros/console.h>
#include <vector>
#include "ldl.c"
#include "matrix_support.c"
#include "solver.c"
#include "util.c"
#include "cowsay.c"

Vars vars;
Params params;
Workspace work;
Settings settings;


mpcControl::mpcControl()
  : mass_(0.5),
    g_(9.81),
    yaw_int_(0.0),
    max_pos_int_(0.5)
{
}

void mpcControl::setMass(const float mass)
{
  mass_ = mass;
}

void mpcControl::setGravity(const float g)
{
  g_ = g;
}

void mpcControl::setPosition(const Eigen::Vector3f &position)
{
  pos_ = position;
}

void mpcControl::setVelocity(const Eigen::Vector3f &velocity)
{
  vel_ = velocity;
}

void mpcControl::setYaw(const float current_yaw)
{
  current_yaw_ = current_yaw;
}

void mpcControl::setMaxIntegral(const float max_integral)
{
  max_pos_int_ = max_integral;
}

void mpcControl::setOptParams( std::vector<double> A,
                               std::vector<double> B,
			       std::vector<double> x_limit,
			       std::vector<double> u_limit)
			       
{ // use this function to get params through the parameter server
 set_defaults();
 setup_indexing();
 load_default_data();
 
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
 
 params.u_limit[0] = u_limit[0];
 params.u_limit[1] = u_limit[1];
 params.u_limit[2] = u_limit[2]; 




}

void mpcControl::calculateControl(const Eigen::Vector3f &des_pos,
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
  
 
 params.x_ref[0] = des_pos[0];
 params.x_ref[1] = des_pos[1];
 params.x_ref[2] = des_pos[2];
 params.x_ref[3] = des_vel[0];
 params.x_ref[4] = des_vel[1];
 params.x_ref[5] = des_vel[2];
 
 params.x_0[0] = pos_[0];
 params.x_0[1] = pos_[1];
 params.x_0[2] = pos_[2];
 params.x_0[3] = vel_[0];
 params.x_0[4] = vel_[1];
 params.x_0[5] = vel_[2];
 
 solve();
 
 trpy_(0) = vars.u_0[2] + mass_*g_; //thrust
 trpy_(1) = vars.u_0[1]; //roll
 trpy_(2) = vars.u_0[0]; //pitch
 trpy_(3) = 0; //yaw
 
 if(0)
 {
char **dummy = (char**) malloc(2 * sizeof(char*));
dummy[1] = (char*) malloc(6 * sizeof(char));
strcpy(dummy[1], "VaNcE");
 cowsay(2, dummy);
 free(dummy[1]);
 free(dummy);
}

}
const Eigen::Vector4f &mpcControl::getControls(void)
{
  return trpy_;
}

void mpcControl::resetIntegrals(void)
{
  pos_int_ = Eigen::Vector3f::Zero();
  yaw_int_ = 0;
}

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
  params.R[0] = 10;
  params.R[3] = 0;
  params.R[6] = 0;
  params.R[1] = 0;
  params.R[4] = 10;
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

  
  params.u_limit[0] = 0.012; // 0.0052 works
  params.u_limit[1] = 0.012;
  params.u_limit[2] = 7;
  params.x_limit[0] = 100;
  params.x_limit[1] = 100;
  params.x_limit[2] = 100;
  params.x_limit[3] = 100;
  params.x_limit[4] = 100;
  params.x_limit[5] = 100;
  params.B[0] = 1;
  params.B[1] = 1;
  params.B[2] = 1;
  params.B[3] = 1;
  params.B[4] = 1;
  params.B[5] = 1;

}



 
