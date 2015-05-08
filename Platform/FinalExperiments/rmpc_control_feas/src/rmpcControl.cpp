#include <rmpc_control/rmpcControl.hpp>
#include <iostream>
#include <rmpc_control/Mode11/solver.h>
#undef SOLVER_H
#include <rmpc_control/Mode22/solver.h>
#undef SOLVER_H
#include <rmpc_control/Mode33/solver.h>
#undef SOLVER_H
#include <rmpc_control/Mode44/solver.h>
#undef SOLVER_H
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ros/console.h>
#include <vector>
#include <cstdlib>
#include <ctime>



static float prev_T; // to store applied inputs for next mpc opt
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

namespace FEAT_150 {
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
FEAT_150_, //34ms  
FEAT_200_, // 38 ms
  NUM_DELAY_MODES
};

static enum DelayMode mode = FEAT_200_;
const float myerr[NUM_DELAY_MODES] ={0.028,0.0237, 0.0231, 0.0113}; //myerr inf norm in m
const float delay[NUM_DELAY_MODES] = {0.024-0.001, 0.029-0.001, 0.034-0.001, 0.038-0.001}; // computation delay in s here
//float err[NUM_DELAY_MODES] = {0.028,0.0237,0.0113}; //err inf norm in m




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

void rmpcControl::calculateControl(
    const Eigen::Vector3f &des_pos, const Eigen::Vector3f &des_vel,
    const Eigen::Vector3f &des_acc, const float des_yaw,
    const Eigen::Vector3f &kx, const Eigen::Vector3f &kv,
    const Eigen::Vector3f &ki, const float ki_yaw)
{ 
  
//add err
//std::cout<<std::endl<<NUM_DELAY_MODES;

//std::cout<<std::endl<<myerr[mode]<<" "<<delay[mode];
srand (static_cast <unsigned> (1235));
float r;
for (int j=0;j<3;j++) {
r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
pos_[j]=pos_[j]+(2*r-1)*myerr[mode];
r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
vel_[j]=vel_[j]+(2*r-1)*myerr[mode];

}

//std::cout<<std::endl<<pos_[0]<<" "<<des_pos[0];

//  optimization
  FEAT_50::UpdateAndsolveOpt(des_pos, des_vel, pos_, vel_, prev_T, prev_R, prev_P);
  FEAT_100::UpdateAndsolveOpt(des_pos, des_vel, pos_, vel_, prev_T, prev_R, prev_P);
  FEAT_150::UpdateAndsolveOpt(des_pos, des_vel, pos_, vel_, prev_T, prev_R, prev_P);
  FEAT_200::UpdateAndsolveOpt(des_pos, des_vel, pos_, vel_, prev_T, prev_R, prev_P);
  
// isnan check

  // optimal mode
  double costs[]={FEAT_50::work.optval,FEAT_100::work.optval+0.000001,FEAT_150::work.optval+0.00000101,FEAT_200::work.optval+0.00000102};//FEAT_150::work.optval+0.000101,
  int ill = indexofSmallestElement(costs,NUM_DELAY_MODES);
/*
 //diagnostics
std::cout<<std::endl<<"mode 0: "<<FEAT_50::work.optval<<" "<<FEAT_50::vars.u_0[2]<<" "<<FEAT_50::vars.u_0[1]<<" "<<FEAT_50::vars.u_0[0];
std::cout<<std::endl<<"mode 1: "<<FEAT_100::work.optval<<" "<<FEAT_100::vars.u_0[2]<<" "<<FEAT_100::vars.u_0[1]<<" "<<FEAT_100::vars.u_0[0];
std::cout<<std::endl<<"mode 2: "<<FEAT_150::work.optval<<" "<<FEAT_150::vars.u_0[2]<<" "<<FEAT_150::vars.u_0[1]<<" "<<FEAT_150::vars.u_0[0];
std::cout<<std::endl<<"mode 3: "<<FEAT_200::work.optval<<" "<<FEAT_200::vars.u_0[2]<<" "<<FEAT_200::vars.u_0[1]<<" "<<FEAT_200::vars.u_0[0];

*/

//std::cout<<std::endl<<FEAT_50::work.converged<<" "<<FEAT_100::work.converged<<" "<<FEAT_150::work.converged<<" "<<FEAT_200::work.converged<<" conv ";
//std::cout<<std::endl<<isnan(costs[0])<<" "<<isnan(costs[1])<<" "<<isnan(costs[2])<<" "<<isnan(costs[3])<<" flt chk ";
std::cout<<std::endl<<"Mode: "<<ill<<" costs [50 100 150 200]: "<<costs[0]<<" "<<costs[1]<<" "<<costs[2]<<" "<<costs[3];
 // std::cout<<std::endl<<"50: "<<FEAT_50::work.optval<<"   100: "<<FEAT_100::work.optval;
  
  float pitch_des;
  float roll_des;
  float thrust_des;
  //ill = 3;//fixed mode
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
   pitch_des = FEAT_150::vars.u_0[0];
   roll_des = FEAT_150::vars.u_0[1];
   thrust_des = FEAT_150::vars.u_0[2];
   mode = FEAT_150_;
  }
  else if(ill==3)
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

void rmpcControl::setOptParams( std::vector<double> A,
		std::vector<double> B,
		std::vector<double> x_limit,
		std::vector<double> u_limit,
		std::vector<double> ZfA_11, 	
		std::vector<double> Zfb_11,
		std::vector<double> ZfA_22, 	
		std::vector<double> Zfb_22,
		std::vector<double> ZfA_33, 	
		std::vector<double> Zfb_33,
		std::vector<double> ZfA_44, 	
		std::vector<double> Zfb_44,
		std::vector<double> ZA_110,                              
		std::vector<double> Zb_110,
		std::vector<double> ZA_111,
		std::vector<double> Zb_111,
		std::vector<double> ZA_112,
		std::vector<double> Zb_112,
		std::vector<double> ZA_113,
		std::vector<double> Zb_113,
		std::vector<double> ZA_114,
		std::vector<double> Zb_114,
		std::vector<double> ZA_115,
		std::vector<double> Zb_115,
		std::vector<double> ZA_116,
		std::vector<double> Zb_116,
		std::vector<double> ZA_117,
		std::vector<double> Zb_117,
		std::vector<double> ZA_118,
		std::vector<double> Zb_118,
		std::vector<double> ZA_119,
		std::vector<double> Zb_119,
		std::vector<double> ZA_1110,
		std::vector<double> Zb_1110,
		std::vector<double> ZA_1111,
		std::vector<double> Zb_1111,
		std::vector<double> ZA_220, 
		std::vector<double> Zb_220,
		std::vector<double> ZA_221,
		std::vector<double> Zb_221,
		std::vector<double> ZA_222,
		std::vector<double> Zb_222,
		std::vector<double> ZA_223,
		std::vector<double> Zb_223,
		std::vector<double> ZA_224,
		std::vector<double> Zb_224,
		std::vector<double> ZA_225,
		std::vector<double> Zb_225,
		std::vector<double> ZA_226,
		std::vector<double> Zb_226,
		std::vector<double> ZA_227,
		std::vector<double> Zb_227,
		std::vector<double> ZA_228,
		std::vector<double> Zb_228,
		std::vector<double> ZA_229,
		std::vector<double> Zb_229,
		std::vector<double> ZA_2210,
		std::vector<double> Zb_2210,          
		std::vector<double> ZA_2211,
		std::vector<double> Zb_2211,
		std::vector<double> ZA_330, 
		std::vector<double> Zb_330,
		std::vector<double> ZA_331,
		std::vector<double> Zb_331,
		std::vector<double> ZA_332,
		std::vector<double> Zb_332,
		std::vector<double> ZA_333,
		std::vector<double> Zb_333,
		std::vector<double> ZA_334,
		std::vector<double> Zb_334,
		std::vector<double> ZA_335,
		std::vector<double> Zb_335,
		std::vector<double> ZA_336,
		std::vector<double> Zb_336,
		std::vector<double> ZA_337,
		std::vector<double> Zb_337,
		std::vector<double> ZA_338,
		std::vector<double> Zb_338,
		std::vector<double> ZA_339,
		std::vector<double> Zb_339,
		std::vector<double> ZA_3310,
		std::vector<double> Zb_3310, 
		std::vector<double> ZA_3311,
		std::vector<double> Zb_3311,
		std::vector<double> ZA_440, 
		std::vector<double> Zb_440,
		std::vector<double> ZA_441,
		std::vector<double> Zb_441,
		std::vector<double> ZA_442,
		std::vector<double> Zb_442,
		std::vector<double> ZA_443,
		std::vector<double> Zb_443,
		std::vector<double> ZA_444,
		std::vector<double> Zb_444,
		std::vector<double> ZA_445,
		std::vector<double> Zb_445,
		std::vector<double> ZA_446,
		std::vector<double> Zb_446,
		std::vector<double> ZA_447,
		std::vector<double> Zb_447,
		std::vector<double> ZA_448,
		std::vector<double> Zb_448,
		std::vector<double> ZA_449,
		std::vector<double> Zb_449,
		std::vector<double> ZA_4410,
		std::vector<double> Zb_4410,
		std::vector<double> ZA_4411,
		std::vector<double> Zb_4411)

{ // use this function to get params through the parameter server
	FEAT_50::set_defaults();
	FEAT_50::setup_indexing();
	FEAT_50::load_default_data();

	//FEAT_50::params.u_limit[0] = u_limit[0];
	//FEAT_50::params.u_limit[1] = u_limit[1];
	//FEAT_50::params.u_limit[2] = u_limit[2];

	FEAT_100::set_defaults();
	FEAT_100::setup_indexing();
	FEAT_100::load_default_data();

	FEAT_150::set_defaults();
	FEAT_150::setup_indexing();
	FEAT_150::load_default_data();


	//FEAT_100::params.u_limit[0] = u_limit[0];
	//FEAT_100::params.u_limit[1] = u_limit[1];
	//FEAT_100::params.u_limit[2] = u_limit[2];

	FEAT_200::set_defaults();
	FEAT_200::setup_indexing();
	FEAT_200::load_default_data();

	// FEAT_200::params.u_limit[0] = u_limit[0];
	// FEAT_200::params.u_limit[1] = u_limit[1];
	// FEAT_200::params.u_limit[2] = u_limit[2];

	// get term sets
	int i; //use this in all loops

	for (i=0; i<18; i++){//Mode 1,1
		FEAT_50::params.Hf[i] = ZfA_11[i];}
	for (i=0;i<18;i++) {//Mode 1,1
		FEAT_50::params.gf[i] =Zfb_11[i];}

	for (i=0; i<18; i++){//Mode 1,1
		FEAT_100::params.Hf[i] = ZfA_22[i];}
	for (i=0;i<18;i++) {//Mode 1,1
		FEAT_100::params.gf[i] =Zfb_22[i];}

	for (i=0; i<18; i++){//Mode 1,1
		FEAT_150::params.Hf[i] = ZfA_33[i];}
	for (i=0;i<18;i++) {//Mode 1,1
		FEAT_150::params.gf[i] =Zfb_33[i];}

	for (i=0; i<18; i++){//Mode 1,1
		FEAT_200::params.Hf[i] = ZfA_44[i];}
	for (i=0;i<18;i++) {//Mode 1,1
		FEAT_200::params.gf[i] =Zfb_44[i];}





	//mode 1,1
	for (i=0;i<18;i++){
		FEAT_50::params.H_0[i] = ZA_110[i];
		FEAT_50::params.g_0[i] = Zb_110[i];
		FEAT_50::params.H_1[i] = ZA_111[i];
		FEAT_50::params.g_1[i] = Zb_111[i];
		FEAT_50::params.H_2[i] = ZA_112[i];
		FEAT_50::params.g_2[i] = Zb_112[i];
		FEAT_50::params.H_3[i] = ZA_113[i];
		FEAT_50::params.g_3[i] = Zb_113[i];
		FEAT_50::params.H_4[i] = ZA_114[i];
		FEAT_50::params.g_4[i] = Zb_114[i];
		FEAT_50::params.H_5[i] = ZA_115[i];
		FEAT_50::params.g_5[i] = Zb_115[i];
		FEAT_50::params.H_6[i] = ZA_116[i];
		FEAT_50::params.g_6[i] = Zb_116[i];
		FEAT_50::params.H_7[i] = ZA_117[i];
		FEAT_50::params.g_7[i] = Zb_117[i];
		FEAT_50::params.H_8[i] = ZA_118[i];
		FEAT_50::params.g_8[i] = Zb_118[i];
		FEAT_50::params.H_9[i] = ZA_119[i];
		FEAT_50::params.g_9[i] = Zb_119[i];
		FEAT_50::params.H_10[i] = ZA_1110[i];
		FEAT_50::params.g_10[i] = Zb_1110[i];
	}//end H,g assignment
	//mode 2,2
	for (i=0;i<18;i++){
		FEAT_100::params.H_0[i] = ZA_220[i];
		FEAT_100::params.g_0[i] = Zb_220[i];
		FEAT_100::params.H_1[i] = ZA_221[i];
		FEAT_100::params.g_1[i] = Zb_221[i];
		FEAT_100::params.H_2[i] = ZA_222[i];
		FEAT_100::params.g_2[i] = Zb_222[i];
		FEAT_100::params.H_3[i] = ZA_223[i];
		FEAT_100::params.g_3[i] = Zb_223[i];
		FEAT_100::params.H_4[i] = ZA_224[i];
		FEAT_100::params.g_4[i] = Zb_224[i];
		FEAT_100::params.H_5[i] = ZA_225[i];
		FEAT_100::params.g_5[i] = Zb_225[i];
		FEAT_100::params.H_6[i] = ZA_226[i];
		FEAT_100::params.g_6[i] = Zb_226[i];
		FEAT_100::params.H_7[i] = ZA_227[i];
		FEAT_100::params.g_7[i] = Zb_227[i];
		FEAT_100::params.H_8[i] = ZA_228[i];
		FEAT_100::params.g_8[i] = Zb_228[i];
		FEAT_100::params.H_9[i] = ZA_229[i];
		FEAT_100::params.g_9[i] = Zb_229[i];
		FEAT_100::params.H_10[i] = ZA_2210[i];
		FEAT_100::params.g_10[i] = Zb_2210[i];
	}//end H,g assignment

	// mode 3,3
	for (i=0;i<18;i++){
		FEAT_150::params.H_0[i] = ZA_330[i];
		FEAT_150::params.g_0[i] = Zb_330[i];
		FEAT_150::params.H_1[i] = ZA_331[i];
		FEAT_150::params.g_1[i] = Zb_331[i];
		FEAT_150::params.H_2[i] = ZA_332[i];
		FEAT_150::params.g_2[i] = Zb_332[i];
		FEAT_150::params.H_3[i] = ZA_333[i];
		FEAT_150::params.g_3[i] = Zb_333[i];
		FEAT_150::params.H_4[i] = ZA_334[i];
		FEAT_150::params.g_4[i] = Zb_334[i];
		FEAT_150::params.H_5[i] = ZA_335[i];
		FEAT_150::params.g_5[i] = Zb_335[i];
		FEAT_150::params.H_6[i] = ZA_336[i];
		FEAT_150::params.g_6[i] = Zb_336[i];
		FEAT_150::params.H_7[i] = ZA_337[i];
		FEAT_150::params.g_7[i] = Zb_337[i];
		FEAT_150::params.H_8[i] = ZA_338[i];
		FEAT_150::params.g_8[i] = Zb_338[i];
		FEAT_150::params.H_9[i] = ZA_339[i];
		FEAT_150::params.g_9[i] = Zb_339[i];
		FEAT_150::params.H_10[i] = ZA_3310[i];
		FEAT_150::params.g_10[i] = Zb_3310[i];
	}//end H,g assignment

	// mode 4,4
	for (i=0;i<18;i++){
		FEAT_200::params.H_0[i] = ZA_440[i];
		FEAT_200::params.g_0[i] = Zb_440[i];
		FEAT_200::params.H_1[i] = ZA_441[i];
		FEAT_200::params.g_1[i] = Zb_441[i];
		FEAT_200::params.H_2[i] = ZA_442[i];
		FEAT_200::params.g_2[i] = Zb_442[i];
		FEAT_200::params.H_3[i] = ZA_443[i];
		FEAT_200::params.g_3[i] = Zb_443[i];
		FEAT_200::params.H_4[i] = ZA_444[i];
		FEAT_200::params.g_4[i] = Zb_444[i];
		FEAT_200::params.H_5[i] = ZA_445[i];
		FEAT_200::params.g_5[i] = Zb_445[i];
		FEAT_200::params.H_6[i] = ZA_446[i];
		FEAT_200::params.g_6[i] = Zb_446[i];
		FEAT_200::params.H_7[i] = ZA_447[i];
		FEAT_200::params.g_7[i] = Zb_447[i];
		FEAT_200::params.H_8[i] = ZA_448[i];
		FEAT_200::params.g_8[i] = Zb_448[i];
		FEAT_200::params.H_9[i] = ZA_449[i];
		FEAT_200::params.g_9[i] = Zb_449[i];
		FEAT_200::params.H_10[i] = ZA_4410[i];
		FEAT_200::params.g_10[i] = Zb_4410[i];
	}//end H,g assignment

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

  //params.u_limit[0] = 0.512; // 0.0052 works
  //params.u_limit[1] = 0.512;
  //params.u_limit[2] = 7;

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

  //params.u_limit[0] = 0.512; // 0.0052 works
  //params.u_limit[1] = 0.512;
  //params.u_limit[2] = 7;


   // 100 features
    params.A_0[0] = 1;
    params.A_0[1] = 0.05;
    params.A_0[2] = 0.0103;
    params.A_0[3] = 1;
    params.A_0[4] = 0.05;
    params.A_0[5] = -0.0103;
    params.A_0[6] = 1;
    params.A_0[7] = 0.05;
    params.A_0[8] = 0.0021;
    params.A_0[9] = 1;
    params.A_0[10] = 0.294;
    params.A_0[11] = 1;
    params.A_0[12] = -0.294;
    params.A_0[13] = 1;
    params.A_0[14] = 0.060;

    params.B_0[0] = 0.0020;
    params.B_0[1] = -0.0020;
    params.B_0[2] = 0.0004;
    params.B_0[3] = 0.1960;
    params.B_0[4] = -0.1960;
    params.B_0[5] = 0.04;
    params.B_0[6] = 1;
    params.B_0[7] = 1;
    params.B_0[8] = 1;

    params.A[0] = 1;
    params.A[1] = 0.05;
    params.A[2] = 0.0103;
    params.A[3] = 1;
    params.A[4] = 0.05;
    params.A[5] = -0.0103;
    params.A[6] = 1;
    params.A[7] = 0.05;
    params.A[8] = 0.0021;
    params.A[9] = 1;
    params.A[10] = 0.294;
    params.A[11] = 1;
    params.A[12] = -0.294;
    params.A[13] = 1;
    params.A[14] = 0.060;

    params.B[0] = 0.002;
    params.B[1] = -0.002;
    params.B[2] = 0.0004;
    params.B[3] = 0.1960;
    params.B[4] = -0.1960;
    params.B[5] = 0.04;
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

namespace FEAT_150 {

void UpdateAndsolveOpt(const Eigen::Vector3f des_pos, const Eigen::Vector3f des_vel, const Eigen::Vector3f pos_, const Eigen::Vector3f vel_, double prev_T, double prev_R, double prev_P)
{
  FEAT_150::params.z_ref[0] = des_pos[0];
  FEAT_150::params.z_ref[1] = des_pos[1];
  FEAT_150::params.z_ref[2] = des_pos[2];
  FEAT_150::params.z_ref[3] = des_vel[0];
  FEAT_150::params.z_ref[4] = des_vel[1];
  FEAT_150::params.z_ref[5] = des_vel[2];
  //std::cout<<std::endl<<FEAT_150::params.z_ref[0]<<" "<<FEAT_150::params.z_ref[1]<<" "<<FEAT_150::params.z_ref[2];//debug
  FEAT_150::params.z_ref[6] = 0; // for the controls
  FEAT_150::params.z_ref[7] = 0;
  FEAT_150::params.z_ref[8] = 0;

  FEAT_150::params.z_0[0] = pos_[0];
  FEAT_150::params.z_0[1] = pos_[1];
  FEAT_150::params.z_0[2] = pos_[2];
  FEAT_150::params.z_0[3] = vel_[0];
  FEAT_150::params.z_0[4] = vel_[1];
  FEAT_150::params.z_0[5] = vel_[2];

  // these are prev controls
  FEAT_150::params.z_0[6] = prev_T;//FEAT_150::vars.u_0[0]; // or use trpy_(2)-m*g and so on
  FEAT_150::params.z_0[7] = prev_R;//FEAT_150::vars.u_0[1];
  FEAT_150::params.z_0[8] = prev_P;//FEAT_150::vars.u_0[2];
  FEAT_150::solve();

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

  //params.u_limit[0] = 0.512; // 0.0052 works
  //params.u_limit[1] = 0.512;
  //params.u_limit[2] = 7;


   // 100 features
    params.A_0[0] = 1;
    params.A_0[1] = 0.05;
    params.A_0[2] = 0.0110;
    params.A_0[3] = 1;
    params.A_0[4] = 0.05;
    params.A_0[5] = -0.0110;
    params.A_0[6] = 1;
    params.A_0[7] = 0.05;
    params.A_0[8] = 0.0022;
    params.A_0[9] = 1;
    params.A_0[10] = 0.3332;
    params.A_0[11] = 1;
    params.A_0[12] = -0.3332;
    params.A_0[13] = 1;
    params.A_0[14] = 0.068;

    params.B_0[0] = 0.0013;
    params.B_0[1] = -0.0013;
    params.B_0[2] = 0.0003;
    params.B_0[3] = 0.1568;
    params.B_0[4] = -0.1568;
    params.B_0[5] = 0.032;
    params.B_0[6] = 1;
    params.B_0[7] = 1;
    params.B_0[8] = 1;

    params.A[0] = 1;
    params.A[1] = 0.05;
    params.A[2] = 0.0110;
    params.A[3] = 1;
    params.A[4] = 0.05;
    params.A[5] = -0.0110;
    params.A[6] = 1;
    params.A[7] = 0.05;
    params.A[8] = 0.0022;
    params.A[9] = 1;
    params.A[10] = 0.3332;
    params.A[11] = 1;
    params.A[12] = -0.3332;
    params.A[13] = 1;
    params.A[14] = 0.068;

    params.B[0] = 0.0013;
    params.B[1] = -0.0013;
    params.B[2] = 0.0003;
    params.B[3] = 0.1568;
    params.B[4] = -0.1568;
    params.B[5] = 0.032;
    params.B[6] = 1;
    params.B[7] = 1;
    params.B[8] = 1;
  } // end  34ms delay, 150 features mode model
} //end namespace



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

  //params.u_limit[0] = 0.512; // 0.0052 works
  //params.u_limit[1] = 0.512;
  //params.u_limit[2] = 7;



    params.A_0[0] = 1;
    params.A_0[1] = 0.05;
    params.A_0[2] = 0.0117;
    params.A_0[3] = 1;
    params.A_0[4] = 0.05;
    params.A_0[5] = -0.0117;
    params.A_0[6] = 1;
    params.A_0[7] = 0.05;
    params.A_0[8] = 0.0022;
    params.A_0[9] = 1;
    params.A_0[10] = 0.3822;
    params.A_0[11] = 1;
    params.A_0[12] = -0.3822;
    params.A_0[13] = 1;
    params.A_0[14] = 0.078;

    params.B_0[0] = 0.0006;
    params.B_0[1] = -0.0006;
    params.B_0[2] = 0.0001;
    params.B_0[3] = 0.1078;
    params.B_0[4] = -0.1078;
    params.B_0[5] = 0.022;
    params.B_0[6] = 1;
    params.B_0[7] = 1;
    params.B_0[8] = 1;

    params.A[0] = 1;
    params.A[1] = 0.05;
    params.A[2] = 0.0117;
    params.A[3] = 1;
    params.A[4] = 0.05;
    params.A[5] = -0.0117;
    params.A[6] = 1;
    params.A[7] = 0.05;
    params.A[8] = 0.0022;
    params.A[9] = 1;
    params.A[10] = 0.3822;
    params.A[11] = 1;
    params.A[12] = -0.3822;
    params.A[13] = 1;
    params.A[14] = 0.078;

    params.B[0] = 0.0006;
    params.B[1] = -0.0006;
    params.B[2] = 0.0001;
    params.B[3] = 0.1078;
    params.B[4] = -0.1078;
    params.B[5] = 0.022;
    params.B[6] = 1;
    params.B[7] = 1;
    params.B[8] = 1;
  // end 38 ms, or 200 corners
 }
}

