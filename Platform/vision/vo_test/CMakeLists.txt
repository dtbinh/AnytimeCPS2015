cmake_minimum_required(VERSION 2.8.3)
project(vo_test)

find_package(cmake_modules)

find_package(catkin REQUIRED COMPONENTS
  vo_utils
  sensor_msgs
  std_msgs
  geometry_msgs
  tf2
  tf2_ros
  rviz_helper
  message_generation
  )

add_service_files(FILES
  SaveTrajectory.srv
  )

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS message_runtime
  )

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  )

set(${PROJECT_NAME}_NODE_SOURCES
  src/node.cpp
  src/main.cpp
  src/error_calculator.cpp
  )

add_definitions("-Wall -Werror -std=c++11")

# Build Node
add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_NODE_SOURCES}
  )

add_dependencies(${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
  ${PROJECT_NAME}_generate_messages_cpp
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  )
