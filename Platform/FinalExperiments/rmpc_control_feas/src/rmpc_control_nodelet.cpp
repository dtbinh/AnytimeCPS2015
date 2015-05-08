#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <nav_msgs/Odometry.h>
#include <quadrotor_msgs/TRPYCommand.h>
#include <quadrotor_msgs/PositionCommand.h>
#include <std_msgs/Bool.h>
#include <rmpc_control/rmpcControl.hpp>
#include <Eigen/Geometry>
#include <tf/transform_datatypes.h>
//#include <rmpc_control/solver.h>
#include <math.h>
#include <vector>
#define CLAMP(x,min,max) ((x) < (min)) ? (min) : ((x) > (max)) ? (max) : (x)

class rmpcControlNodelet : public nodelet::Nodelet
{
 public:
  rmpcControlNodelet() :
      position_cmd_updated_(false),
      position_cmd_init_(false),
      des_yaw_(0),
      current_yaw_(0),
      idle_motors_(false),
      enable_motors_(false),
      use_external_yaw_(false)
  {
  }

  void onInit(void);

 private:
  void publishTRPYCommand(void);
  void position_cmd_callback(const quadrotor_msgs::PositionCommand::ConstPtr &cmd);
  void odom_callback(const nav_msgs::Odometry::ConstPtr &odom);
  void enable_motors_callback(const std_msgs::Bool::ConstPtr &msg);

  rmpcControl controller_;
  ros::Publisher trpy_command_pub_;
  ros::Subscriber odom_sub_;
  ros::Subscriber position_cmd_sub_;
  ros::Subscriber enable_motors_sub_;

  bool position_cmd_updated_, position_cmd_init_;
  std::string frame_id_;

  Eigen::Vector3f des_pos_, des_vel_, des_acc_, kx_, kv_, ki_, kR_, kOm_;
  float des_yaw_;
  float current_yaw_;
  float ki_yaw_;
  float max_roll_pitch_;
  bool enable_motors_, idle_motors_;
  bool use_external_yaw_;
};


void rmpcControlNodelet::publishTRPYCommand(void)
{
  
  enable_motors_ = 1; //enable for sim, remove in real
  float ki_yaw = 0;
  Eigen::Vector3f ki = Eigen::Vector3f::Zero();
  // Only enable integral terms when motors are on
  if(enable_motors_)
  {
    ki_yaw = ki_yaw_;
    ki = ki_;
  }
  controller_.calculateControl(des_pos_, des_vel_, des_acc_, des_yaw_, kx_, kv_, ki, ki_yaw);

  const Eigen::Vector4f &trpy = controller_.getControls();

  quadrotor_msgs::TRPYCommand::Ptr trpy_command(new quadrotor_msgs::TRPYCommand);
  trpy_command->header.stamp = ros::Time::now();
  trpy_command->header.frame_id = frame_id_;
  if(enable_motors_)
  {
    trpy_command->thrust = trpy(0);
    trpy_command->roll   = CLAMP(trpy(1), -max_roll_pitch_, max_roll_pitch_);
    trpy_command->pitch  = CLAMP(trpy(2), -max_roll_pitch_, max_roll_pitch_);
    trpy_command->yaw    = trpy(3);
    trpy_command->kR[0] = kR_[0];
    trpy_command->kR[1] = kR_[1];
    trpy_command->kR[2] = kR_[2];
    trpy_command->kOm[0] = kOm_[0];
    trpy_command->kOm[1] = kOm_[1];
    trpy_command->kOm[2] = kOm_[2];
  }
  else if(idle_motors_)
  {
    trpy_command->thrust = 0.001*9.81*1.01; // slightly above 1 gram
    trpy_command->roll   = 0;
    trpy_command->pitch  = 0;
    trpy_command->yaw    = 0;
  }
  trpy_command->aux.current_yaw = current_yaw_;
  trpy_command->aux.enable_motors = enable_motors_;
  trpy_command->aux.use_external_yaw = use_external_yaw_;

  trpy_command_pub_.publish(trpy_command);
}

void rmpcControlNodelet::position_cmd_callback(const quadrotor_msgs::PositionCommand::ConstPtr &cmd)
{
  des_pos_ = Eigen::Vector3f(cmd->position.x, cmd->position.y, cmd->position.z);
  des_vel_ = Eigen::Vector3f(cmd->velocity.x, cmd->velocity.y, cmd->velocity.z);
  des_acc_ = Eigen::Vector3f(cmd->acceleration.x, cmd->acceleration.y, cmd->acceleration.z);
  kx_ = Eigen::Vector3f(cmd->kx[0], cmd->kx[1], cmd->kx[2]);
  kv_ = Eigen::Vector3f(cmd->kv[0], cmd->kv[1], cmd->kv[2]);

  des_yaw_ = cmd->yaw;
  position_cmd_updated_ = true;
  //position_cmd_init_ = true;

  publishTRPYCommand();
}

void rmpcControlNodelet::odom_callback(const nav_msgs::Odometry::ConstPtr &odom)
{
  const Eigen::Vector3f position(odom->pose.pose.position.x,
                                 odom->pose.pose.position.y,
                                 odom->pose.pose.position.z);
  const Eigen::Vector3f velocity(odom->twist.twist.linear.x,
                                 odom->twist.twist.linear.y,
                                 odom->twist.twist.linear.z);

  current_yaw_ = tf::getYaw(odom->pose.pose.orientation);

  controller_.setPosition(position);
  controller_.setVelocity(velocity);
  controller_.setYaw(current_yaw_);

  if(position_cmd_init_)
  {
    // We set position_cmd_updated_ = false and expect that the
    // position_cmd_callback would set it to true since typically a position_cmd
    // message would follow an odom message. If not, the position_cmd_callback
    // hasn't been called and we publish the so3 command ourselves
    // TODO: Fallback to hover if position_cmd hasn't been received for some time
    if(!position_cmd_updated_)
      publishTRPYCommand();
    position_cmd_updated_ = false;
  }
}

void rmpcControlNodelet::enable_motors_callback(const std_msgs::Bool::ConstPtr &msg)
{
  if(msg->data)
  {
    if(!idle_motors_)
    {
      ROS_INFO("Idling motors");
      idle_motors_ = true;
    }
    else
    {
      ROS_INFO("Enabling motors2");
      enable_motors_ = true;
    }
  }
  else
  {
    ROS_INFO("Disabling motors");
    enable_motors_ = false;
    idle_motors_ = false;
  }

  controller_.resetIntegrals();
}

void rmpcControlNodelet::onInit(void)
{
  ros::NodeHandle n(getPrivateNodeHandle());

  std::string quadrotor_name;
  n.param("quadrotor_name", quadrotor_name, std::string("quadrotor"));
  frame_id_ = "/" + quadrotor_name;

  double mass;
  n.param("mass", mass, 0.235);
  controller_.setMass(mass);
  controller_.setMaxIntegral(mass*3);

  n.param("use_external_yaw", use_external_yaw_, true);

  double max_roll_pitch;
  n.param("max_roll_pitch", max_roll_pitch, 30.0);
  max_roll_pitch_ = max_roll_pitch;

  double ki_x, ki_y, ki_z, ki_yaw;
  n.param("gains/ki/x", ki_x, 0.0);
  n.param("gains/ki/y", ki_y, 0.0);
  n.param("gains/ki/z", ki_z, 0.0);
  n.param("gains/ki/yaw", ki_yaw, 0.01);
  ki_[0] = ki_x, ki_[1] = ki_y, ki_[2] = ki_z;
  ki_yaw_ = ki_yaw;

  double kR[3], kOm[3];

  // try reading some params
  std::vector<double> A;
  std::vector<double> B;
  std::vector<double> x_limit;
  std::vector<double> u_limit;
 //term sets 
std::vector<double> ZfA_11; 
  std::vector<double> Zfb_11;
  
std::vector<double> ZfA_22; 
  std::vector<double> Zfb_22;
  
std::vector<double> ZfA_33; 
  std::vector<double> Zfb_33;
  
std::vector<double> ZfA_44; 
  std::vector<double> Zfb_44;
  //sets for mode 1,1
std::vector<double>ZA_110;
  std::vector<double> Zb_110;
std::vector<double> ZA_111;
  std::vector<double> Zb_111;
std::vector<double> ZA_112;
  std::vector<double> Zb_112;
std::vector<double> ZA_113;
  std::vector<double> Zb_113;
std::vector<double> ZA_114;
  std::vector<double> Zb_114;
std::vector<double> ZA_115;
  std::vector<double> Zb_115;
std::vector<double> ZA_116;
  std::vector<double> Zb_116;
std::vector<double> ZA_117;
  std::vector<double> Zb_117;
std::vector<double> ZA_118;
  std::vector<double> Zb_118;
std::vector<double> ZA_119;
  std::vector<double> Zb_119;
std::vector<double> ZA_1110;
  std::vector<double> Zb_1110;
std::vector<double> ZA_1111;
  std::vector<double> Zb_1111;
  //sets for mode 2,2
std::vector<double> ZA_220;
  std::vector<double> Zb_220;
std::vector<double> ZA_221;
  std::vector<double> Zb_221;
std::vector<double> ZA_222;
  std::vector<double> Zb_222;
std::vector<double> ZA_223;
  std::vector<double> Zb_223;
std::vector<double> ZA_224;
  std::vector<double> Zb_224;
std::vector<double> ZA_225;
  std::vector<double> Zb_225;
std::vector<double> ZA_226;
  std::vector<double> Zb_226;
std::vector<double> ZA_227;
  std::vector<double> Zb_227;
std::vector<double> ZA_228;
  std::vector<double> Zb_228;
std::vector<double> ZA_229;
  std::vector<double> Zb_229;
std::vector<double> ZA_2210;
  std::vector<double> Zb_2210;
std::vector<double> ZA_2211;
  std::vector<double> Zb_2211;
 //sets for mode 3,3
std::vector<double> ZA_330;
  std::vector<double> Zb_330;
std::vector<double> ZA_331;
  std::vector<double> Zb_331;
std::vector<double> ZA_332;
  std::vector<double> Zb_332;
std::vector<double> ZA_333;
  std::vector<double> Zb_333;
std::vector<double> ZA_334;
  std::vector<double> Zb_334;
std::vector<double> ZA_335;
  std::vector<double> Zb_335;
std::vector<double> ZA_336;
  std::vector<double> Zb_336;
std::vector<double> ZA_337;
  std::vector<double> Zb_337;
std::vector<double> ZA_338;
  std::vector<double> Zb_338;
std::vector<double> ZA_339;
  std::vector<double> Zb_339;
std::vector<double> ZA_3310;
  std::vector<double> Zb_3310;
std::vector<double> ZA_3311;
  std::vector<double> Zb_3311;
 //sets for mode 4,4
std::vector<double> ZA_440;
  std::vector<double> Zb_440;
std::vector<double> ZA_441;
  std::vector<double> Zb_441;
std::vector<double> ZA_442;
  std::vector<double> Zb_442;
std::vector<double> ZA_443;
  std::vector<double> Zb_443;
std::vector<double> ZA_444;
  std::vector<double> Zb_444;
std::vector<double> ZA_445;
  std::vector<double> Zb_445;
std::vector<double> ZA_446;
  std::vector<double> Zb_446;
std::vector<double> ZA_447;
  std::vector<double> Zb_447;
std::vector<double> ZA_448;
  std::vector<double> Zb_448;
std::vector<double> ZA_449;
  std::vector<double> Zb_449;
std::vector<double> ZA_4410;
  std::vector<double> Zb_4410;
std::vector<double> ZA_4411;
  std::vector<double> Zb_4411;



  if((n.getParam("A",A)) && (n.getParam("B",B)) && (n.getParam("x_limit",x_limit)) && (n.getParam("u_limit",u_limit)))
  {
    ROS_INFO("Got all Params");
  }
  else
  {
    ROS_ERROR("Failed: Params not loaded");
  }
 //get term sets
  if(n.getParam("ZfA_11",ZfA_11))
  {ROS_INFO(" term params");}
  else {ROS_ERROR("No term  params");}

  n.getParam("ZfA_11",ZfA_11);
  n.getParam("Zfb_11",Zfb_11);
  n.getParam("ZfA_11",ZfA_22);
  n.getParam("Zfb_11",Zfb_22);
  n.getParam("ZfA_11",ZfA_33);
  n.getParam("Zfb_11",Zfb_33);
  n.getParam("ZfA_11",ZfA_44);
  n.getParam("Zfb_11",Zfb_44);
  //get other sets
  //mode 1,1
  if(n.getParam("ZA_110",ZA_110))
  {ROS_INFO(" Mode 1 params");}
  else {ROS_ERROR("No Mode 1 params");}


  n.getParam("ZA_110",ZA_110);
  n.getParam("Zb_110",Zb_110);
  n.getParam("ZA_110",ZA_111);
  n.getParam("Zb_110",Zb_111);
  n.getParam("ZA_110",ZA_112);
  n.getParam("Zb_110",Zb_112);
  n.getParam("ZA_110",ZA_113);
  n.getParam("Zb_110",Zb_113);
  n.getParam("ZA_110",ZA_114);
  n.getParam("Zb_110",Zb_114);
  n.getParam("ZA_110",ZA_115);
  n.getParam("Zb_110",Zb_115);
  n.getParam("ZA_110",ZA_116);
  n.getParam("Zb_110",Zb_116);
  n.getParam("ZA_110",ZA_117);
  n.getParam("Zb_110",Zb_117);
  n.getParam("ZA_110",ZA_118);
  n.getParam("Zb_110",Zb_118);
  n.getParam("ZA_110",ZA_119);
  n.getParam("Zb_110",Zb_119);
  n.getParam("ZA_110",ZA_1110);
  n.getParam("Zb_110",Zb_1110);
  n.getParam("ZA_110",ZA_1111);
  n.getParam("Zb_110",Zb_1111);
  //mode 2,2
  if(n.getParam("ZA_220",ZA_220))
  {ROS_INFO(" Mode 2 params");}
  else {ROS_ERROR("No Mode 2 params");}

  n.getParam("ZA_220",ZA_220);
  n.getParam("Zb_220",Zb_220);
  n.getParam("ZA_220",ZA_221);
  n.getParam("Zb_220",Zb_221);
  n.getParam("ZA_220",ZA_222);
  n.getParam("Zb_220",Zb_222);
  n.getParam("ZA_220",ZA_223);
  n.getParam("Zb_220",Zb_223);
  n.getParam("ZA_220",ZA_224);
  n.getParam("Zb_220",Zb_224);
  n.getParam("ZA_220",ZA_225);
  n.getParam("Zb_220",Zb_225);
  n.getParam("ZA_220",ZA_226);
  n.getParam("Zb_220",Zb_226);
  n.getParam("ZA_220",ZA_227);
  n.getParam("Zb_220",Zb_227);
  n.getParam("ZA_220",ZA_228);
  n.getParam("Zb_220",Zb_228);
  n.getParam("ZA_220",ZA_229);
  n.getParam("Zb_220",Zb_229);
  n.getParam("ZA_220",ZA_2210);
  n.getParam("Zb_220",Zb_2210);
  n.getParam("ZA_220",ZA_2211);
  n.getParam("Zb_220",Zb_2211);

  //mode 3,3
  if(n.getParam("ZA_330",ZA_330))
  {ROS_INFO(" Mode 3 params");}
  else {ROS_ERROR("No Mode 3 params");}

  n.getParam("ZA_330",ZA_330);
  n.getParam("Zb_330",Zb_330);
  n.getParam("ZA_330",ZA_331);
  n.getParam("Zb_330",Zb_331);
  n.getParam("ZA_330",ZA_332);
  n.getParam("Zb_330",Zb_332);
  n.getParam("ZA_330",ZA_333);
  n.getParam("Zb_330",Zb_333);
  n.getParam("ZA_330",ZA_334);
  n.getParam("Zb_330",Zb_334);
  n.getParam("ZA_330",ZA_335);
  n.getParam("Zb_330",Zb_335);
  n.getParam("ZA_330",ZA_336);
  n.getParam("Zb_330",Zb_336);
  n.getParam("ZA_330",ZA_337);
  n.getParam("Zb_330",Zb_337);
  n.getParam("ZA_330",ZA_338);
  n.getParam("Zb_330",Zb_338);
  n.getParam("ZA_330",ZA_339);
  n.getParam("Zb_330",Zb_339);
  n.getParam("ZA_330",ZA_3310);
  n.getParam("Zb_330",Zb_3310);
  n.getParam("ZA_330",ZA_3311);
  n.getParam("Zb_330",Zb_3311);

  //mode 4,4
  if(n.getParam("ZA_440",ZA_440))
  {ROS_INFO(" Mode 4 params");}
  else {ROS_ERROR("No Mode 4 params");}

  n.getParam("ZA_440",ZA_440);
  n.getParam("Zb_440",Zb_440);
  n.getParam("ZA_440",ZA_441);
  n.getParam("Zb_440",Zb_441);
  n.getParam("ZA_440",ZA_442);
  n.getParam("Zb_440",Zb_442);
  n.getParam("ZA_440",ZA_443);
  n.getParam("Zb_440",Zb_443);
  n.getParam("ZA_440",ZA_444);
  n.getParam("Zb_440",Zb_444);
  n.getParam("ZA_440",ZA_445);
  n.getParam("Zb_440",Zb_445);
  n.getParam("ZA_440",ZA_446);
  n.getParam("Zb_440",Zb_446);
  n.getParam("ZA_440",ZA_447);
  n.getParam("Zb_440",Zb_447);
  n.getParam("ZA_440",ZA_448);
  n.getParam("Zb_440",Zb_448);
  n.getParam("ZA_440",ZA_449);
  n.getParam("Zb_440",Zb_449);
  n.getParam("ZA_440",ZA_4410);
  n.getParam("Zb_440",Zb_4410);
  n.getParam("ZA_440",ZA_4411);
  n.getParam("Zb_440",Zb_4411);

  // send to the rmpc
  controller_.setOptParams(A,B,x_limit,u_limit, 
		  ZfA_11, Zfb_11, ZfA_22, Zfb_22, ZfA_33, Zfb_33, ZfA_44, Zfb_44, 
		  ZA_110, Zb_110, ZA_111, Zb_111, ZA_112, Zb_112, ZA_113,Zb_113,
		  ZA_114, Zb_114, ZA_115, Zb_115, ZA_116, Zb_116, ZA_117,Zb_117,
		  ZA_118, Zb_118, ZA_119, Zb_119, ZA_1110,Zb_1110,ZA_1111, Zb_1111,
		  ZA_220, Zb_220, ZA_221, Zb_221, ZA_222, Zb_222, ZA_223,Zb_223,
		  ZA_224, Zb_224, ZA_225, Zb_225, ZA_226, Zb_226, ZA_227,Zb_227,
		  ZA_228, Zb_228, ZA_229, Zb_229, ZA_2210,Zb_2210,ZA_2211, Zb_2211,
		  ZA_330, Zb_330, ZA_331, Zb_331, ZA_332, Zb_332, ZA_333,Zb_333,     
		  ZA_334, Zb_334, ZA_335, Zb_335, ZA_336, Zb_336, ZA_337,Zb_337,
		  ZA_338, Zb_338, ZA_339, Zb_339, ZA_3310,Zb_3310,ZA_3311, Zb_3311,
		  ZA_440, Zb_440, ZA_441, Zb_441, ZA_442, Zb_442, ZA_443,Zb_443,
		  ZA_444, Zb_444, ZA_445, Zb_445, ZA_446, Zb_446, ZA_447,Zb_447,
		  ZA_448, Zb_448, ZA_449, Zb_449, ZA_4410,Zb_4410,ZA_4411, Zb_4411);


  // back to everyday stuff
  n.param("gains/rot/x", kR[0], 1.5);
  n.param("gains/rot/y", kR[1], 1.5);
  n.param("gains/rot/z", kR[2], 1.0);
  n.param("gains/ang/x", kOm[0], 0.13);
  n.param("gains/ang/y", kOm[1], 0.13);
  n.param("gains/ang/z", kOm[2], 0.1);
  kR_[0] = kR[0], kR_[1] = kR[1], kR_[2] = kR[2];
  kOm_[0] = kOm[0], kOm_[1] = kOm[1], kOm_[2] = kOm[2];

  odom_sub_ = n.subscribe("odom", 10, &rmpcControlNodelet::odom_callback, this,
		  ros::TransportHints().tcpNoDelay());
  position_cmd_sub_ = n.subscribe("position_cmd", 10, &rmpcControlNodelet::position_cmd_callback, this,
		  ros::TransportHints().tcpNoDelay());

  enable_motors_sub_ = n.subscribe("motors", 2, &rmpcControlNodelet::enable_motors_callback, this,
		  ros::TransportHints().tcpNoDelay());

  trpy_command_pub_ = n.advertise<quadrotor_msgs::TRPYCommand>("trpy_cmd", 10);
}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rmpcControlNodelet, nodelet::Nodelet);
