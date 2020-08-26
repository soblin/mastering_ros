cmake_minimum_required(VERSION 2.8.3)
project(mastering_ros_robot_description_pkg)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  rviz
  tf
  urdf
  xacro
)

catkin_package()
