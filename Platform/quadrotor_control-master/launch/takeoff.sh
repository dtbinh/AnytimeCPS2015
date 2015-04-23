#!/bin/bash

rostopic pub -1 /quadcloud2/motors std_msgs/Bool 0

rostopic pub -1 /quadcloud2/controllers_manager/line_tracker_min_jerk/goal geometry_msgs/Vector3 "{x: 0.0, y: 0.0, z: 0.0}"
rosservice call /quadcloud2/controllers_manager/transition line_tracker/LineTrackerMinJerk

echo "Idling"
rostopic pub -1 /quadcloud2/motors std_msgs/Bool 1
rostopic pub -1 /quadcloud2/motors std_msgs/Bool 1

echo "Takeoff"
rostopic pub -1 /quadcloud2/controllers_manager/line_tracker_min_jerk/goal geometry_msgs/Vector3 "{x: 0.0, y: 0.0, z: 0.2}"
