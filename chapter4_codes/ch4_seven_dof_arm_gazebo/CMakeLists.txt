cmake_minimum_required(VERSION 3.0.2)
project(ch4_seven_dof_arm_gazebo)

find_package(catkin REQUIRED COMPONENTS
  gazebo_msgs
  gazebo_plugins
  gazebo_ros
  gazebo_ros_control
)

catkin_package()
