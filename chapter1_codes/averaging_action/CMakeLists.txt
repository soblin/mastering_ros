cmake_minimum_required(VERSION 2.8.3)
project(averaging_action)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  roscpp
  rospy
  std_msgs
  message_generation
  message_runtime
  )

find_package(Boost REQUIRED COMPONENTS
  system
  )

add_action_files(
  FILES
  Averaging.action
  )

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  actionlib_msgs
  std_msgs
  )

catkin_package(
  CATKIN_DEPENDS actionlib actionlib_msgs roscpp rospy std_msgs message_runtime
  DEPENDS system_lib
  )

include_directories(
  # include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INLCUDE_DIRS}
  )

add_executable(averaging_server_node src/averaging_server.cpp)
add_executable(averaging_client_node src/averaging_client.cpp)

add_dependencies(averaging_server_node averaging_action_generate_messages_cpp)
add_dependencies(averaging_client_node averaging_action_generate_messages_cpp)

# error : undefined reference to `boost::system::generic_category()
# is generated if you failed to write properly
target_link_libraries(averaging_server_node ${catkin_LIBRARIES})
target_link_libraries(averaging_client_node ${catkin_LIBRARIES})

file(GLOB srcs
  "src/*"
  )

find_program(CLANG_FORMAT_EXE clang-format)
if(CLANG_FORMAT_EXE)
  add_custom_target(${PROJECT_NAME}-format ALL
    COMMAND clang-format --style=file -i ${srcs}
    COMMENT "Running clang-format"
    VERBATIM
    )
endif()
