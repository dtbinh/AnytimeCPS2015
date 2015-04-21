cmake_minimum_required(VERSION 2.8.3)
project(vo_utils)

find_package(catkin REQUIRED cmake_modules)
find_package(Eigen REQUIRED)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

include("cmake/extras.cmake")

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES vo_utils
#  CATKIN_DEPENDS other_catkin_pkg
  DEPENDS Eigen
  CFG_EXTRAS "extras.cmake"
)

include_directories(include
  ${EIGEN_INCLUDE_DIRS})

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)
