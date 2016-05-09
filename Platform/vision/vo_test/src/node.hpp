#ifndef NODE_HPP
#define NODE_HPP

#include <ros/ros.h>
#include <ros/node_handle.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <tf2/buffer_core.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/transform_broadcaster.h>

#include <vo_test/error_calculator.hpp>
#include <vo_test/SaveTrajectory.h>

#include <rviz_helper/marker_visualizer.hpp>

#include <memory>

namespace vo {
namespace test {

class Node {
public:
  
  Node();
  
public:
  
  void configureTopics();
  
  void callback(const nav_msgs::OdometryConstPtr& odom_vision,
                const nav_msgs::OdometryConstPtr& odom_vicon);  
  
  bool serviceCallback(vo_test::SaveTrajectoryRequest&,
                       vo_test::SaveTrajectoryResponse&);
  
  bool calcScale_;
  std::size_t count_{0};
  Pose vicon1st_, vicon2nd_;
  Pose vision1st_, vision2nd_;
  double scale_{1};
  double outputRate_{0.25};
  bool enableLogging_{true};
  std::string viconChildFrameId_;
  
  vo::test::ErrorCalculator errorCalc_;
      
  ros::NodeHandle nh_;
  tf2::BufferCore tfCore_;
  tf2_ros::TransformListener tfListener_;
  tf2_ros::TransformBroadcaster tfBroadcaster_;
  
  message_filters::Subscriber<nav_msgs::Odometry> subVision_;
  message_filters::Subscriber<nav_msgs::Odometry> subVicon_;
  
  //  time sync policies
  typedef message_filters::sync_policies::ApproximateTime<
    nav_msgs::Odometry,
    nav_msgs::Odometry> TimeSyncVicon;
  
  static constexpr int kQueueSize = 300;
  
  std::shared_ptr<message_filters::Synchronizer<TimeSyncVicon>> syncVicon_;
  
  //  publishers/subscribers
  ros::Publisher pubTransformedOdom_; 

  ros::Publisher VisionPubPose_; //publish pose type messages
  ros::Publisher ViconPubPose_; 

  ros::ServiceServer srvSave_;
  
  std::shared_ptr<kr::viz::TrajectoryVisualizer> trajVizVicon_;
  std::shared_ptr<kr::viz::TrajectoryVisualizer> trajVizVision_;
};

} //  test
} //  vo

#endif // NODE_HPP
