#include <rmpc_control/rmpcControl.hpp>
#include <iostream>
#include <rmpc_control/Mode1/solver.h>
#undef SOLVER_H
#include <rmpc_control/Mode2/solver.h>
#undef SOLVER_H
#include <rmpc_control/Mode3/solver.h>
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

static float prev_T;
static float prev_R;
static float prev_P;

int indexofSmallestElement(double array[], int size); 

namespace FEAT_200 {
Vars vars;
Params params;
Workspace work;
Settings settings;
void UpdateAndsolveOpt(const Eigen::Vector3f des_pos, const Eigen::Vector3f des_vel, const Eigen::Vector3f pos_, const Eigen::Vector3f vel_, double prev_T, double prev_R, double prev_P);
}

namespace FEAT_100 {
Vars vars;
Params params;
Workspace work;
Settings settings;
void UpdateAndsolveOpt(const Eigen::Vector3f des_pos, const Eigen::Vector3f des_vel, const Eigen::Vector3f pos_, const Eigen::Vector3f vel_, double prev_T, double prev_R, double prev_P);
}

namespace FEAT_50 {
Vars vars;
Params params;
Workspace work;
Settings settings;
void UpdateAndsolveOpt(const Eigen::Vector3f des_pos, const Eigen::Vector3f des_vel, const Eigen::Vector3f pos_, const Eigen::Vector3f vel_, double prev_T, double prev_R, double prev_P);
}

//using namespace FEAT_50;


enum DelayMode
{
  FEAT_50_, // 24 ms
  FEAT_100_, // 29 ms
  FEAT_200_, // 38 ms
  NUM_DELAY_MODES
};

enum DelayMode mode = FEAT_200_;
float delay[NUM_DELAY_MODES] = {0.024, 0.029, 0.038}; // computation delay in s here

rmpcControl::rmpcControl()
    : mass_(0.5), g_(9.81), yaw_int_(0.0), max_pos_int_(0.5)
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

void rmpcControl::setOptParams(std::vector<double> A, std::vector<double> B,
                               std::vector<double> x_limit,
                               std::vector<double> u_limit)

{ // use this function to get params through the parameter server
  FEAT_50::set_defaults();
  FEAT_50::setup_indexing();
  FEAT_50::load_default_data();
 
  FEAT_50::params.u_limit[0] = u_limit[0];
  FEAT_50::params.u_limit[1] = u_limit[1];
  FEAT_50::params.u_limit[2] = u_limit[2];
  
  FEAT_100::set_defaults();
  FEAT_100::setup_indexing();
  FEAT_100::load_default_data();
 
  FEAT_100::params.u_limit[0] = u_limit[0];
  FEAT_100::params.u_limit[1] = u_limit[1];
  FEAT_100::params.u_limit[2] = u_limit[2];

  FEAT_200::set_defaults();
  FEAT_200::setup_indexing();
  FEAT_200::load_default_data();
 
  FEAT_200::params.u_limit[0] = u_limit[0];
  FEAT_200::params.u_limit[1] = u_limit[1];
  FEAT_200::params.u_limit[2] = u_limit[2];

}

void rmpcControl::calculateControl(
    const Eigen::Vector3f &des_pos, const Eigen::Vector3f &des_vel,
    const Eigen::Vector3f &des_acc, const float des_yaw,
    const Eigen::Vector3f &kx, const Eigen::Vector3f &kv,
    const Eigen::Vector3f &ki, const float ki_yaw)
{ 
  //  optimization
  FEAT_50::UpdateAndsolveOpt(des_pos, des_vel, pos_, vel_, prev_T, prev_R, prev_P);
  FEAT_100::UpdateAndsolveOpt(des_pos, des_vel, pos_, vel_, prev_T, prev_R, prev_P);
  FEAT_200::UpdateAndsolveOpt(des_pos, des_vel, pos_, vel_, prev_T, prev_R, prev_P);

// isnan check

  // optimal mode
  double costs[]={FEAT_50::work.optval,FEAT_100::work.optval+0.0001,FEAT_200::work.optval+0.000102};
  int ill = indexofSmallestElement(costs,3);
  std::cout<<std::endl<<"Mode: "<<ill<<" costs [50 100 200]: "<<costs[0]<<" "<<costs[1]<<" "<<costs[2];
 // std::cout<<std::endl<<"50: "<<FEAT_50::work.optval<<"   100: "<<FEAT_100::work.optval;
  
  float pitch_des;
  float roll_des;
  float thrust_des;

  if(ill==0)
  {
   pitch_des = FEAT_50::vars.u_0[0];
   roll_des = FEAT_50::vars.u_0[1];
   thrust_des = FEAT_50::vars.u_0[2];
   mode = FEAT_50_;
  }
  else if(ill==1)
  {
   pitch_des = FEAT_100::vars.u_0[0];
   roll_des = FEAT_100::vars.u_0[1];
   thrust_des = FEAT_100::vars.u_0[2];
   mode = FEAT_100_;
  }
  else if(ill==2)
  {
   pitch_des = FEAT_200::vars.u_0[0];
   roll_des = FEAT_200::vars.u_0[1];
   thrust_des = FEAT_200::vars.u_0[2];
   mode = FEAT_200_;
  }



  /*else
  {
   pitch_des = 0;
   roll_des = 0;
   thrust_des = 0;
  }*/



// Need to transform these to the correct frame using the current yaw of robot

  trpy_(0) = thrust_des + mass_ * g_; // thrust
  trpy_(1) = roll_des * cos(current_yaw_) + pitch_des * sin(current_yaw_);
  trpy_(2) = pitch_des * cos(current_yaw_) - roll_des * sin(current_yaw_);
  trpy_(3) = 0; // yaw
 
   

  // update prev inputs
  prev_T = thrust_des;
  prev_R = roll_des;
  prev_P = pitch_des;

}

const Eigen::Vector4f &rmpcControl::getControls(void)
{
  ros::Duration(delay[mode]).sleep(); // add delay
  return trpy_;
}

void rmpcControl::resetIntegrals(void)
{
  pos_int_ = Eigen::Vector3f::Zero();
  yaw_int_ = 0;
}

int indexofSmallestElement(double array[], int size)
{
    int index = 0;

    for(int i = 1; i < size; i++)
    {
        if(array[i] < array[index])
            index = i;              
    }

    return index;
}



namespace FEAT_50 {

void UpdateAndsolveOpt(const Eigen::Vector3f des_pos, const Eigen::Vector3f des_vel, const Eigen::Vector3f pos_, const Eigen::Vector3f vel_, double prev_T, double prev_R, double prev_P)
{
  FEAT_50::params.z_ref[0] = des_pos[0];
  FEAT_50::params.z_ref[1] = des_pos[1];
  FEAT_50::params.z_ref[2] = des_pos[2];
  FEAT_50::params.z_ref[3] = des_vel[0];
  FEAT_50::params.z_ref[4] = des_vel[1];
  FEAT_50::params.z_ref[5] = des_vel[2];
  //std::cout<<std::endl<<FEAT_50::params.z_ref[0]<<" "<<FEAT_50::params.z_ref[1]<<" "<<FEAT_50::params.z_ref[2];//debug
  FEAT_50::params.z_ref[6] = 0; // for the controls
  FEAT_50::params.z_ref[7] = 0;
  FEAT_50::params.z_ref[8] = 0;

  FEAT_50::params.z_0[0] = pos_[0];
  FEAT_50::params.z_0[1] = pos_[1];
  FEAT_50::params.z_0[2] = pos_[2];
  FEAT_50::params.z_0[3] = vel_[0];
  FEAT_50::params.z_0[4] = vel_[1];
  FEAT_50::params.z_0[5] = vel_[2];

  // these are prev controls
  FEAT_50::params.z_0[6] = prev_T;//FEAT_50::vars.u_0[0]; // or use trpy_(2)-m*g and so on
  FEAT_50::params.z_0[7] = prev_R;//FEAT_50::vars.u_0[1];
  FEAT_50::params.z_0[8] = prev_P;//FEAT_50::vars.u_0[2];
  FEAT_50::solve();

}




void load_default_data(void)
{
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
  params.Q[30] = 0.1;
  params.Q[39] = 0;
  params.Q[48] = 0;
  params.Q[57] = 0;
  params.Q[66] = 0;
  params.Q[75] = 0;
  params.Q[4] = 0;
  params.Q[13] = 0;
  params.Q[22] = 0;
  params.Q[31] = 0;
  params.Q[40] = 0.1;
  params.Q[49] = 0;
  params.Q[58] = 0;
  params.Q[67] = 0;
  params.Q[76] = 0;
  params.Q[5] = 0;
  params.Q[14] = 0;
  params.Q[23] = 0;
  params.Q[32] = 0;
  params.Q[41] = 0;
  params.Q[50] = 0.1;
  params.Q[59] = 0;
  params.Q[68] = 0;
  params.Q[77] = 0;
  params.Q[6] = 0;
  params.Q[15] = 0;
  params.Q[24] = 0;
  params.Q[33] = 0;
  params.Q[42] = 0;
  params.Q[51] = 0;
  params.Q[60] = 5;
  params.Q[69] = 0;
  params.Q[78] = 0;
  params.Q[7] = 0;
  params.Q[16] = 0;
  params.Q[25] = 0;
  params.Q[34] = 0;
  params.Q[43] = 0;
  params.Q[52] = 0;
  params.Q[61] = 0;
  params.Q[70] = 5;
  params.Q[79] = 0;
  params.Q[8] = 0;
  params.Q[17] = 0;
  params.Q[26] = 0;
  params.Q[35] = 0;
  params.Q[44] = 0;
  params.Q[53] = 0;
  params.Q[62] = 0;
  params.Q[71] = 0;
  params.Q[80] = 1;

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
  params.Q_final[30] = 0.1;
  params.Q_final[39] = 0;
  params.Q_final[48] = 0;
  params.Q_final[57] = 0;
  params.Q_final[66] = 0;
  params.Q_final[75] = 0;
  params.Q_final[4] = 0;
  params.Q_final[13] = 0;
  params.Q_final[22] = 0;
  params.Q_final[31] = 0;
  params.Q_final[40] = 0.1;
  params.Q_final[49] = 0;
  params.Q_final[58] = 0;
  params.Q_final[67] = 0;
  params.Q_final[76] = 0;
  params.Q_final[5] = 0;
  params.Q_final[14] = 0;
  params.Q_final[23] = 0;
  params.Q_final[32] = 0;
  params.Q_final[41] = 0;
  params.Q_final[50] = 0.1;
  params.Q_final[59] = 0;
  params.Q_final[68] = 0;
  params.Q_final[77] = 0;
  params.Q_final[6] = 0;
  params.Q_final[15] = 0;
  params.Q_final[24] = 0;
  params.Q_final[33] = 0;
  params.Q_final[42] = 0;
  params.Q_final[51] = 0;
  params.Q_final[60] = 5;
  params.Q_final[69] = 0;
  params.Q_final[78] = 0;
  params.Q_final[7] = 0;
  params.Q_final[16] = 0;
  params.Q_final[25] = 0;
  params.Q_final[34] = 0;
  params.Q_final[43] = 0;
  params.Q_final[52] = 0;
  params.Q_final[61] = 0;
  params.Q_final[70] = 5;
  params.Q_final[79] = 0;
  params.Q_final[8] = 0;
  params.Q_final[17] = 0;
  params.Q_final[26] = 0;
  params.Q_final[35] = 0;
  params.Q_final[44] = 0;
  params.Q_final[53] = 0;
  params.Q_final[62] = 0;
  params.Q_final[71] = 0;
  params.Q_final[80] = 1;

  params.u_limit[0] = 0.512; // 0.0052 works
  params.u_limit[1] = 0.512;
  params.u_limit[2] = 7;

    params.A_0[0] = 1;
    params.A_0[1] = 0.05;
    params.A_0[2] = 0.0089;
    params.A_0[3] = 1;
    params.A_0[4] = 0.05;
    params.A_0[5] = -0.0089;
    params.A_0[6] = 1;
    params.A_0[7] = 0.05;
    params.A_0[8] = 0.0018;
    params.A_0[9] = 1;
    params.A_0[10] = 0.2352;
    params.A_0[11] = 1;
    params.A_0[12] = -0.2352;
    params.A_0[13] = 1;
    params.A_0[14] = 0.048;

    params.B_0[0] = 0.0033;
    params.B_0[1] = -0.0033;
    params.B_0[2] = 0.0007;
    params.B_0[3] = 0.2548;
    params.B_0[4] = -0.2548;
    params.B_0[5] = 0.052;
    params.B_0[6] = 1;
    params.B_0[7] = 1;
    params.B_0[8] = 1;

    params.A[0] = 1;
    params.A[1] = 0.05;
    params.A[2] = 0.0089;
    params.A[3] = 1;
    params.A[4] = 0.05;
    params.A[5] = -0.0089;
    params.A[6] = 1;
    params.A[7] = 0.05;
    params.A[8] = 0.0018;
    params.A[9] = 1;
    params.A[10] = 0.2352;
    params.A[11] = 1;
    params.A[12] = -0.2352;
    params.A[13] = 1;
    params.A[14] = 0.048;

    params.B[0] = 0.0033;
    params.B[1] = -0.0033;
    params.B[2] = 0.0007;
    params.B[3] = 0.2548;
    params.B[4] = -0.2548;
    params.B[5] = 0.052;
    params.B[6] = 1;
    params.B[7] = 1;
    params.B[8] = 1;

  
   }//end funcn
}//end namespace

namespace FEAT_100 {

void UpdateAndsolveOpt(const Eigen::Vector3f des_pos, const Eigen::Vector3f des_vel, const Eigen::Vector3f pos_, const Eigen::Vector3f vel_, double prev_T, double prev_R, double prev_P)
{
  FEAT_100::params.z_ref[0] = des_pos[0];
  FEAT_100::params.z_ref[1] = des_pos[1];
  FEAT_100::params.z_ref[2] = des_pos[2];
  FEAT_100::params.z_ref[3] = des_vel[0];
  FEAT_100::params.z_ref[4] = des_vel[1];
  FEAT_100::params.z_ref[5] = des_vel[2];
  //std::cout<<std::endl<<FEAT_100::params.z_ref[0]<<" "<<FEAT_100::params.z_ref[1]<<" "<<FEAT_100::params.z_ref[2];//debug
  FEAT_100::params.z_ref[6] = 0; // for the controls
  FEAT_100::params.z_ref[7] = 0;
  FEAT_100::params.z_ref[8] = 0;

  FEAT_100::params.z_0[0] = pos_[0];
  FEAT_100::params.z_0[1] = pos_[1];
  FEAT_100::params.z_0[2] = pos_[2];
  FEAT_100::params.z_0[3] = vel_[0];
  FEAT_100::params.z_0[4] = vel_[1];
  FEAT_100::params.z_0[5] = vel_[2];

  // these are prev controls
  FEAT_100::params.z_0[6] = prev_T;//FEAT_100::vars.u_0[0]; // or use trpy_(2)-m*g and so on
  FEAT_100::params.z_0[7] = prev_R;//FEAT_100::vars.u_0[1];
  FEAT_100::params.z_0[8] = prev_P;//FEAT_100::vars.u_0[2];
  FEAT_100::solve();

}

void load_default_data(void)
{
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
  params.Q[30] = 0.1;
  params.Q[39] = 0;
  params.Q[48] = 0;
  params.Q[57] = 0;
  params.Q[66] = 0;
  params.Q[75] = 0;
  params.Q[4] = 0;
  params.Q[13] = 0;
  params.Q[22] = 0;
  params.Q[31] = 0;
  params.Q[40] = 0.1;
  params.Q[49] = 0;
  params.Q[58] = 0;
  params.Q[67] = 0;
  params.Q[76] = 0;
  params.Q[5] = 0;
  params.Q[14] = 0;
  params.Q[23] = 0;
  params.Q[32] = 0;
  params.Q[41] = 0;
  params.Q[50] = 0.1;
  params.Q[59] = 0;
  params.Q[68] = 0;
  params.Q[77] = 0;
  params.Q[6] = 0;
  params.Q[15] = 0;
  params.Q[24] = 0;
  params.Q[33] = 0;
  params.Q[42] = 0;
  params.Q[51] = 0;
  params.Q[60] = 5;
  params.Q[69] = 0;
  params.Q[78] = 0;
  params.Q[7] = 0;
  params.Q[16] = 0;
  params.Q[25] = 0;
  params.Q[34] = 0;
  params.Q[43] = 0;
  params.Q[52] = 0;
  params.Q[61] = 0;
  params.Q[70] = 5;
  params.Q[79] = 0;
  params.Q[8] = 0;
  params.Q[17] = 0;
  params.Q[26] = 0;
  params.Q[35] = 0;
  params.Q[44] = 0;
  params.Q[53] = 0;
  params.Q[62] = 0;
  params.Q[71] = 0;
  params.Q[80] = 1;

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
  params.Q_final[30] = 0.1;
  params.Q_final[39] = 0;
  params.Q_final[48] = 0;
  params.Q_final[57] = 0;
  params.Q_final[66] = 0;
  params.Q_final[75] = 0;
  params.Q_final[4] = 0;
  params.Q_final[13] = 0;
  params.Q_final[22] = 0;
  params.Q_final[31] = 0;
  params.Q_final[40] = 0.1;
  params.Q_final[49] = 0;
  params.Q_final[58] = 0;
  params.Q_final[67] = 0;
  params.Q_final[76] = 0;
  params.Q_final[5] = 0;
  params.Q_final[14] = 0;
  params.Q_final[23] = 0;
  params.Q_final[32] = 0;
  params.Q_final[41] = 0;
  params.Q_final[50] = 0.1;
  params.Q_final[59] = 0;
  params.Q_final[68] = 0;
  params.Q_final[77] = 0;
  params.Q_final[6] = 0;
  params.Q_final[15] = 0;
  params.Q_final[24] = 0;
  params.Q_final[33] = 0;
  params.Q_final[42] = 0;
  params.Q_final[51] = 0;
  params.Q_final[60] = 5;
  params.Q_final[69] = 0;
  params.Q_final[78] = 0;
  params.Q_final[7] = 0;
  params.Q_final[16] = 0;
  params.Q_final[25] = 0;
  params.Q_final[34] = 0;
  params.Q_final[43] = 0;
  params.Q_final[52] = 0;
  params.Q_final[61] = 0;
  params.Q_final[70] = 5;
  params.Q_final[79] = 0;
  params.Q_final[8] = 0;
  params.Q_final[17] = 0;
  params.Q_final[26] = 0;
  params.Q_final[35] = 0;
  params.Q_final[44] = 0;
  params.Q_final[53] = 0;
  params.Q_final[62] = 0;
  params.Q_final[71] = 0;
  params.Q_final[80] = 1;

  params.u_limit[0] = 0.512; // 0.0052 works
  params.u_limit[1] = 0.512;
  params.u_limit[2] = 7;


   // 100 features
    params.A_0[0] = 1;
    params.A_0[1] = 0.05;
    params.A_0[2] = 0.0101;
    params.A_0[3] = 1;
    params.A_0[4] = 0.05;
    params.A_0[5] = -0.0101;
    params.A_0[6] = 1;
    params.A_0[7] = 0.05;
    params.A_0[8] = 0.0021;
    params.A_0[9] = 1;
    params.A_0[10] = 0.2842;
    params.A_0[11] = 1;
    params.A_0[12] = -0.2842;
    params.A_0[13] = 1;
    params.A_0[14] = 0.058;

    params.B_0[0] = 0.0022;
    params.B_0[1] = -0.0022;
    params.B_0[2] = 0.0004;
    params.B_0[3] = 0.2058;
    params.B_0[4] = -0.2058;
    params.B_0[5] = 0.042;
    params.B_0[6] = 1;
    params.B_0[7] = 1;
    params.B_0[8] = 1;

    params.A[0] = 1;
    params.A[1] = 0.05;
    params.A[2] = 0.0101;
    params.A[3] = 1;
    params.A[4] = 0.05;
    params.A[5] = -0.0101;
    params.A[6] = 1;
    params.A[7] = 0.05;
    params.A[8] = 0.0021;
    params.A[9] = 1;
    params.A[10] = 0.2842;
    params.A[11] = 1;
    params.A[12] = -0.2842;
    params.A[13] = 1;
    params.A[14] = 0.058;

    params.B[0] = 0.0022;
    params.B[1] = -0.0022;
    params.B[2] = 0.0004;
    params.B[3] = 0.2058;
    params.B[4] = -0.2058;
    params.B[5] = 0.042;
    params.B[6] = 1;
    params.B[7] = 1;
    params.B[8] = 1;
  } // end 29 ms delay, 100 features mode model
} //end namespace
/*  else if(mode == FEAT_50_)
  { // 50 features
    params.A_0[0] = 1;
    params.A_0[1] = 0.05;
    params.A_0[2] = 0.0089;
    params.A_0[3] = 1;
    params.A_0[4] = 0.05;
    params.A_0[5] = -0.0089;
    params.A_0[6] = 1;
    params.A_0[7] = 0.05;
    params.A_0[8] = 0.0018;
    params.A_0[9] = 1;
    params.A_0[10] = 0.2352;
    params.A_0[11] = 1;
    params.A_0[12] = -0.2352;
    params.A_0[13] = 1;
    params.A_0[14] = 0.048;

    params.B_0[0] = 0.0033;
    params.B_0[1] = -0.0033;
    params.B_0[2] = 0.0007;
    params.B_0[3] = 0.2548;
    params.B_0[4] = -0.2548;
    params.B_0[5] = 0.052;
    params.B_0[6] = 1;
    params.B_0[7] = 1;
    params.B_0[8] = 1;

    params.A[0] = 1;
    params.A[1] = 0.05;
    params.A[2] = 0.0089;
    params.A[3] = 1;
    params.A[4] = 0.05;
    params.A[5] = -0.0089;
    params.A[6] = 1;
    params.A[7] = 0.05;
    params.A[8] = 0.0018;
    params.A[9] = 1;
    params.A[10] = 0.2352;
    params.A[11] = 1;
    params.A[12] = -0.2352;
    params.A[13] = 1;
    params.A[14] = 0.048;

    params.B[0] = 0.0033;
    params.B[1] = -0.0033;
    params.B[2] = 0.0007;
    params.B[3] = 0.2548;
    params.B[4] = -0.2548;
    params.B[5] = 0.052;
    params.B[6] = 1;
    params.B[7] = 1;
    params.B[8] = 1;
  } // end 24 ms delay, 50 features mode model
}
*/

namespace FEAT_200 {

void UpdateAndsolveOpt(const Eigen::Vector3f des_pos, const Eigen::Vector3f des_vel, const Eigen::Vector3f pos_, const Eigen::Vector3f vel_, double prev_T, double prev_R, double prev_P)
{
  FEAT_200::params.z_ref[0] = des_pos[0];
  FEAT_200::params.z_ref[1] = des_pos[1];
  FEAT_200::params.z_ref[2] = des_pos[2];
  FEAT_200::params.z_ref[3] = des_vel[0];
  FEAT_200::params.z_ref[4] = des_vel[1];
  FEAT_200::params.z_ref[5] = des_vel[2];
  //std::cout<<std::endl<<FEAT_200::params.z_ref[0]<<" "<<FEAT_200::params.z_ref[1]<<" "<<FEAT_200::params.z_ref[2];//debug
  FEAT_200::params.z_ref[6] = 0; // for the controls
  FEAT_200::params.z_ref[7] = 0;
  FEAT_200::params.z_ref[8] = 0;

  FEAT_200::params.z_0[0] = pos_[0];
  FEAT_200::params.z_0[1] = pos_[1];
  FEAT_200::params.z_0[2] = pos_[2];
  FEAT_200::params.z_0[3] = vel_[0];
  FEAT_200::params.z_0[4] = vel_[1];
  FEAT_200::params.z_0[5] = vel_[2];

  // these are prev controls
  FEAT_200::params.z_0[6] = prev_T;//FEAT_200::vars.u_0[0]; // or use trpy_(2)-m*g and so on
  FEAT_200::params.z_0[7] = prev_R;//FEAT_200::vars.u_0[1];
  FEAT_200::params.z_0[8] = prev_P;//FEAT_200::vars.u_0[2];
  FEAT_200::solve();

}



void load_default_data(void)
{
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
  params.Q[30] = 0.1;
  params.Q[39] = 0;
  params.Q[48] = 0;
  params.Q[57] = 0;
  params.Q[66] = 0;
  params.Q[75] = 0;
  params.Q[4] = 0;
  params.Q[13] = 0;
  params.Q[22] = 0;
  params.Q[31] = 0;
  params.Q[40] = 0.1;
  params.Q[49] = 0;
  params.Q[58] = 0;
  params.Q[67] = 0;
  params.Q[76] = 0;
  params.Q[5] = 0;
  params.Q[14] = 0;
  params.Q[23] = 0;
  params.Q[32] = 0;
  params.Q[41] = 0;
  params.Q[50] = 0.1;
  params.Q[59] = 0;
  params.Q[68] = 0;
  params.Q[77] = 0;
  params.Q[6] = 0;
  params.Q[15] = 0;
  params.Q[24] = 0;
  params.Q[33] = 0;
  params.Q[42] = 0;
  params.Q[51] = 0;
  params.Q[60] = 5;
  params.Q[69] = 0;
  params.Q[78] = 0;
  params.Q[7] = 0;
  params.Q[16] = 0;
  params.Q[25] = 0;
  params.Q[34] = 0;
  params.Q[43] = 0;
  params.Q[52] = 0;
  params.Q[61] = 0;
  params.Q[70] = 5;
  params.Q[79] = 0;
  params.Q[8] = 0;
  params.Q[17] = 0;
  params.Q[26] = 0;
  params.Q[35] = 0;
  params.Q[44] = 0;
  params.Q[53] = 0;
  params.Q[62] = 0;
  params.Q[71] = 0;
  params.Q[80] = 1;

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
  params.Q_final[30] = 0.1;
  params.Q_final[39] = 0;
  params.Q_final[48] = 0;
  params.Q_final[57] = 0;
  params.Q_final[66] = 0;
  params.Q_final[75] = 0;
  params.Q_final[4] = 0;
  params.Q_final[13] = 0;
  params.Q_final[22] = 0;
  params.Q_final[31] = 0;
  params.Q_final[40] = 0.1;
  params.Q_final[49] = 0;
  params.Q_final[58] = 0;
  params.Q_final[67] = 0;
  params.Q_final[76] = 0;
  params.Q_final[5] = 0;
  params.Q_final[14] = 0;
  params.Q_final[23] = 0;
  params.Q_final[32] = 0;
  params.Q_final[41] = 0;
  params.Q_final[50] = 0.1;
  params.Q_final[59] = 0;
  params.Q_final[68] = 0;
  params.Q_final[77] = 0;
  params.Q_final[6] = 0;
  params.Q_final[15] = 0;
  params.Q_final[24] = 0;
  params.Q_final[33] = 0;
  params.Q_final[42] = 0;
  params.Q_final[51] = 0;
  params.Q_final[60] = 5;
  params.Q_final[69] = 0;
  params.Q_final[78] = 0;
  params.Q_final[7] = 0;
  params.Q_final[16] = 0;
  params.Q_final[25] = 0;
  params.Q_final[34] = 0;
  params.Q_final[43] = 0;
  params.Q_final[52] = 0;
  params.Q_final[61] = 0;
  params.Q_final[70] = 5;
  params.Q_final[79] = 0;
  params.Q_final[8] = 0;
  params.Q_final[17] = 0;
  params.Q_final[26] = 0;
  params.Q_final[35] = 0;
  params.Q_final[44] = 0;
  params.Q_final[53] = 0;
  params.Q_final[62] = 0;
  params.Q_final[71] = 0;
  params.Q_final[80] = 1;

  params.u_limit[0] = 0.512; // 0.0052 works
  params.u_limit[1] = 0.512;
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
  // end 38 ms, or 200 corners
 }
}

