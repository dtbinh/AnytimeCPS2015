cmake_minimum_required(VERSION 2.8.3)
project(mpc_control)

# set default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

find_package(catkin REQUIRED COMPONENTS roscpp nav_msgs quadrotor_msgs std_msgs nodelet tf cmake_modules)
find_package(Eigen REQUIRED)

include_directories(include ${catkin_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIR})

catkin_package(
  INCLUDE_DIRS
  LIBRARIES
  CATKIN_DEPENDS roscpp nav_msgs quadrotor_msgs std_msgs nodelet tf
  DEPENDS Eigen)

add_library(mpcControl src/mpcControl.cpp) # src/solver.c src/ldl.c src/matrix_support.c src/util.c)
#add_library(solver src/solver.c)
#add_library(util src/util.c)
#add_library(ldl src/ldl.c)
#add_library(matrix_support src/matrix_support.c)
add_library(mpc_control_nodelet src/mpc_control_nodelet.cpp)
add_dependencies(mpc_control_nodelet ${catkin_EXPORTED_TARGETS})
target_link_libraries(mpc_control_nodelet mpcControl ${catkin_LIBRARIES})
