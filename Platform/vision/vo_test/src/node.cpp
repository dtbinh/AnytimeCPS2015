#include "node.hpp"
#include <vo_utils/pose.hpp>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE* logFile_x;
FILE* logFile_y;
FILE* logFile_z;

namespace vo {
namespace test {

Node::Node() :  nh_("~"),
  tfListener_(tfCore_), tfBroadcaster_() {

  //  if true, we will calculate scale automatically
  nh_.param("calculate_scale", calcScale_, true);
  nh_.param("enable_logging", enableLogging_, true);
  nh_.param("vicon_child_frame_id", viconChildFrameId_, std::string());

  configureTopics();
}

void Node::configureTopics() {
  subVision_.subscribe(nh_, "vision_odom", kQueueSize);
  subVicon_.subscribe(nh_, "vicon_odom", kQueueSize);

  syncVicon_.reset(new message_filters::Synchronizer<TimeSyncVicon>(
                      TimeSyncVicon(kQueueSize), subVision_, subVicon_));

  syncVicon_->registerCallback(
      boost::bind(&Node::callback, this, _1, _2));

  pubTransformedOdom_ =
      nh_.advertise<nav_msgs::Odometry>("transformed_odometry", 1);

  srvSave_ = nh_.advertiseService(std::string("save"),
                                  &Node::serviceCallback, this);

  trajVizVicon_.reset( new kr::viz::TrajectoryVisualizer(nh_, "vicon_trajectory") );
  trajVizVicon_->SetColor(kr::viz::colors::RED);
  trajVizVicon_->SetAlpha(1);
  trajVizVicon_->set_num_skip(1);
  trajVizVicon_->SetScale(0.05);

  trajVizVision_.reset( new kr::viz::TrajectoryVisualizer(nh_, "vision_trajectory") );
  trajVizVision_->SetColor(kr::viz::colors::GREEN);
  trajVizVision_->SetAlpha(1);
  trajVizVision_->set_num_skip(1);
  trajVizVision_->SetScale(0.05);
}

void Node::callback(const nav_msgs::OdometryConstPtr& odom_vision,
                    const nav_msgs::OdometryConstPtr& odom_vicon) {

  //  id of the vicon model base link
  std::string vicon_base_frame = odom_vicon->child_frame_id;
  //  id of the camera frame
  std::string vision_frame = odom_vision->child_frame_id;

  if (!viconChildFrameId_.empty()) {
    vicon_base_frame = viconChildFrameId_;
    ROS_WARN_ONCE_NAMED("vicon_override",
                        "Warning, vicon child frame id has been manually set to %s",
                        viconChildFrameId_.c_str());
  }

  //  convert vision pose to vicon base link
  Pose H_vicon_vision;
  const std::string trans_name = vision_frame + "_to_" + vicon_base_frame;
  try {
    ROS_INFO_ONCE_NAMED(trans_name, "Getting transform from %s to %s",
                        vision_frame.c_str(), vicon_base_frame.c_str());
    const geometry_msgs::TransformStamped transform = tfCore_.lookupTransform(
        vicon_base_frame, vision_frame, ros::Time(0));

    H_vicon_vision = Pose(transform); //  stereo 2 base link
  }
  catch (const tf2::TransformException& e) {
    ROS_ERROR("Failed while getting transform from %s to %s",
              vision_frame.c_str(), vicon_base_frame.c_str());
    ROS_ERROR("%s", e.what());
    return;
  }

  //  incoming vision to world odom, as determined by vicon
  const Pose H_w_vic(odom_vicon->pose.pose);
  const Pose H_w_vis = H_w_vic.compose(H_vicon_vision);

  //  vision to world, estimated
  const Pose H_w_vis_est(odom_vision->pose.pose);

  if (count_ == 0) {
    vision1st_ = H_w_vis_est;
    vicon1st_ = H_w_vis;
    count_++;
    ROS_INFO_STREAM("First vision pose: " << vision1st_.matrix());
    ROS_INFO_STREAM("First vicon pose: " << vicon1st_.matrix());
  }
  else if (count_ == 1) {
    //  check if we meet the min translation to calculate scale
    vec3 diff = H_w_vis.t() - vicon1st_.t();
    if ( diff.norm() > 0.5 ) {
      vision2nd_ = H_w_vis_est;
      vicon2nd_ = H_w_vis;
      count_++;
      ROS_INFO_STREAM("Second vision pose: " << vision2nd_.matrix());
      ROS_INFO_STREAM("Second vicon pose: " << vicon2nd_.matrix());
    }
  }
  else {
    if (calcScale_) {
      //  compute the scale factor
      //  we are assuming there has been reasonable motion here
      const double vicon_scale =
          (vicon1st_.t() -  vicon2nd_.t()).norm();

      const double vision_scale =
          (vision1st_.t() - vision2nd_.t()).norm();

      scale_ = vicon_scale / vision_scale;
      ROS_INFO("Initializing scale to %f", scale_);
      calcScale_ = false;
    }

    //  translate to origin of vision1st
    const vec3 pos = (H_w_vis_est.t() - vision1st_.t())*scale_;

    //  rotate into frame of vicon 1st
    const quat R_vic1_vis1 = vicon1st_.rot() * vision1st_.rot().conjugate();
    const quat rot = R_vic1_vis1 * H_w_vis_est.rot();

    //  transformed into the vicon frame
    const Pose H_w_vis_act(rot, R_vic1_vis1.matrix()*pos + vicon1st_.t());

    errorCalc_.addFrame(H_w_vis_act, H_w_vis,
                        odom_vision->header.stamp.toNSec());

    //  calculate some error metrics...
    if (enableLogging_) {
      auto rms_x = errorCalc_.positionStats(0).rms();
      auto rms_y = errorCalc_.positionStats(1).rms();
      auto rms_z = errorCalc_.positionStats(2).rms();
      
      // write abs error into file(s)
      logFile_x = fopen("/home/mlab-retro/data_log/logF_err_x.txt","a");
      logFile_y = fopen("/home/mlab-retro/data_log/logF_err_y.txt","a");
      logFile_z = fopen("/home/mlab-retro/data_log/logF_err_z.txt","a");
      fprintf(logFile_x,"%f \n",rms_x);
      fflush(logFile_x);
      fprintf(logFile_y,"%f \n",rms_y);
      fflush(logFile_y);
      fprintf(logFile_z,"%f \n",rms_z);
      fflush(logFile_z);

      auto rms_rx = errorCalc_.rotationStats(0).rms() * 180.0/M_PI;
      auto rms_ry = errorCalc_.rotationStats(1).rms() * 180.0/M_PI;
      auto rms_rz = errorCalc_.rotationStats(2).rms() * 180.0/M_PI;
      auto len = errorCalc_.pathLength();

      //  dump some informative stuff to the log
      ROS_ERROR_THROTTLE_NAMED(outputRate_,"path_len", "Path length: %f", len);

      const auto norm = std::sqrt(rms_x*rms_x + rms_y*rms_y + rms_z*rms_z);
      ROS_ERROR_THROTTLE_NAMED(outputRate_,"position_error_rms",
                                 "RMS position error x/y/z (norm, percent): %f/%f/%f (%f, %f)",
                                  rms_x, rms_y, rms_z,
                                  norm,
                                  norm /  len * 100);
      ROS_ERROR_THROTTLE_NAMED(outputRate_,"rotation_error_rms",
                                 "RMS rotation error (deg) x/y/z: %f/%f/%f",
                                  rms_rx, rms_ry, rms_rz);
    }

    //  publish some topics
    std_msgs::Header header;
    header.stamp = odom_vision->header.stamp;
    header.frame_id = "world";
    trajVizVision_->PublishTrajectory(static_cast<geometry_msgs::Pose>(H_w_vis_act).position,
                                      header);

    trajVizVicon_->PublishTrajectory(static_cast<geometry_msgs::Pose>(H_w_vis).position,
                                     header);
    count_++;
  }
}

bool Node::serviceCallback(vo_test::SaveTrajectoryRequest& request,
                           vo_test::SaveTrajectoryResponse&) {
  const std::string& path = request.path;
  ROS_INFO("Will try to save to %s", path.c_str());

  std::ofstream ofs;
  ofs.open(path.c_str(), std::ofstream::out);
  if (ofs.is_open()) {
    //  write all the poses
    ofs << errorCalc_;
    ofs.close();
  } else {
    ROS_ERROR("Failed to open file!");
  }

  return true;
}

} //  test
} //  vo
