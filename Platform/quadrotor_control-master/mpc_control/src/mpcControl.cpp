#include <mpc_control/mpcControl.hpp>
#include <iostream>
#include <mpc_control/solver.h>
#include <math.h>
#include "solver.h"
#include <time.h>
#include <stdlib.h>


#include "ldl.c"
#include "matrix_support.c"
#include "solver.c"
#include "util.c"


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

  //std::cout << pos_int_.transpose() << std::endl;
 
 set_defaults();
 setup_indexing();
 load_default_data();
 
 
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
// std::cout<<std::endl<<params.u_limit[0];  
//reset_rand();
/* set_defaults();
setup_indexing();
load_default_data();
std::cout<<std::endl<<params.u_limit[0];  */
  
  //
  
  /*
  Eigen::Vector3f force_des = kx.asDiagonal()*e_pos + pos_int_ + kv.asDiagonal()*e_vel + mass_*des_acc
      + mass_*g_*Eigen::Vector3f(0,0,1);

  float roll_des = (force_des(0)*sin(current_yaw_) - force_des(1)*cos(current_yaw_))/force_des(2);
  float pitch_des = (force_des(0)*cos(current_yaw_) + force_des(1)*sin(current_yaw_))/force_des(2);

  float e_yaw = (des_yaw - current_yaw_);
  if(e_yaw > M_PI)
    e_yaw -= 2*M_PI;
  else if(e_yaw < -M_PI)
    e_yaw += 2*M_PI;

  yaw_int_ += ki_yaw*e_yaw;
  if(yaw_int_ > M_PI)
    yaw_int_ = M_PI;
  else if(yaw_int_ < -M_PI)
    yaw_int_ = -M_PI;

  float yaw_cmd = des_yaw + yaw_int_;
  if(yaw_cmd > M_PI)
    yaw_cmd -= 2*M_PI;
  else if(yaw_cmd < -M_PI)
    yaw_cmd += 2*M_PI;

  trpy_(0) = force_des(2);
  trpy_(1) = roll_des;
  trpy_(2) = pitch_des;
  trpy_(3) = yaw_cmd; */
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
  
  params.u_limit[0] = 0.012; // 0.0052 works
  params.u_limit[1] = 0.012;
  params.u_limit[2] = 7;
  params.x_limit[0] = 100;
  params.x_limit[1] = 100;
  params.x_limit[2] = 100;
  params.x_limit[3] = 100;
  params.x_limit[4] = 100;
  params.x_limit[5] = 100;
}


 
