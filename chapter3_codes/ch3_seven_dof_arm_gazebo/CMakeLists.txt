cmake_minimum_required(VERSION 2.8.3)
project(ch3_seven_dof_arm_gazebo)

find_package(catkin REQUIRED COMPONENTS
  gazebo_msgs
  gazebo_plugins
  gazebo_ros
  gazebo_ros_control
  geometry_msgs
  roscpp
  rospy
  rviz
  tf
  urdf
  xacro
)

catkin_package()
