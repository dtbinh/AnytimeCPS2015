cmake_minimum_required(VERSION 2.8.3)
project(rmpc_control)

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

add_library(rmpcControl src/rmpcControl.cpp src/opt/Mode11/solver.cpp src/opt/Mode11/ldl.cpp src/opt/Mode11/matrix_support.cpp src/opt/Mode11/util.cpp src/opt/Mode22/solver.cpp src/opt/Mode22/ldl.cpp src/opt/Mode22/matrix_support.cpp src/opt/Mode22/util.cpp src/opt/Mode33/solver.cpp src/opt/Mode33/ldl.cpp src/opt/Mode33/matrix_support.cpp src/opt/Mode33/util.cpp src/opt/Mode44/solver.cpp src/opt/Mode44/ldl.cpp src/opt/Mode44/matrix_support.cpp src/opt/Mode44/util.cpp         )
#  src/opt/Mode2/solver.cpp src/opt/Mode2/ldl.cpp src/opt/Mode2/matrix_support.cpp src/opt/Mode2/util.cpp )
target_link_libraries(rmpcControl ${catkin_LIBRARIES})

#add_library(solver src/solver.c)
#add_library(util src/util.c)
#add_library(ldl src/ldl.c)
#add_library(matrix_support src/matrix_support.c)
add_library(rmpc_control_nodelet src/rmpc_control_nodelet.cpp)
add_dependencies(rmpc_control_nodelet ${catkin_EXPORTED_TARGETS})
target_link_libraries(rmpc_control_nodelet rmpcControl ${catkin_LIBRARIES})
