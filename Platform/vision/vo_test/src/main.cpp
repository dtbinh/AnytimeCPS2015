//	main.cpp
#include <ros/ros.h>
#include "node.hpp"

int main(int argc, char ** argv) {
  ros::init(argc, argv, "vo_test");
  vo::test::Node node;
  ros::spin();
  return 0;
}
