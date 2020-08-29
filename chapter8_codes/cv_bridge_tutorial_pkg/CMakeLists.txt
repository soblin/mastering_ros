cmake_minimum_required(VERSION 3.0.2)
project(cv_bridge_tutorial_pkg)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
  )

find_package(OpenCV 3 REQUIRED)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  )

add_executable(${PROJECT_NAME}_node src/sample_cv_bridge_node.cpp)

set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME sample_cv_bridge_node PREFIX "")

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
  )

file(GLOB srcs
  "src/*"
  )

find_program(CLANG_FORMAT_EXE clang-format)

if(CLANG_FORMAT_EXE)
  add_custom_target(${PROJECT_NAME}-format ALL
    COMMAND ${CLANG_FORMAT_EXE} --style=file -i ${srcs}
    COMMENT "Running clang-format in ${PROJECT_NAME}"
    VERBATIM
    )
endif()
