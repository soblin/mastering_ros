cmake_minimum_required(VERSION 3.0.2)
project(my_controller_pkg)

add_compile_options(-std=c++11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED COMPONENTS
  pluginlib
  pr2_controller_interface
  pr2_mechanism_model
  roscpp
  )

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES my_controller_pkg
  CATKIN_DEPENDS pluginlib pr2_controller_interface pr2_mechanism_model roscpp
  DEPENDS Boost
  )

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  )

add_library(my_controller_lib
  src/my_controller_file.cpp
  )

target_link_libraries(my_controller_lib
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
  )

file(GLOB srcs
  "/include/my_controller_pkg/*"
  "src/*"
  )

find_program(CLANG_FORMAT_EXE clang-format)
if(CLANG_FORMAT_EXE)
  add_custom_target(${PROJECT_NAME}-format ALL
    COMMAND clang-format --style=file -i ${srcs}
    COMMENT "Running clang-format in ${PROJECT_NAME}"
    VERBATIM)
endif()
