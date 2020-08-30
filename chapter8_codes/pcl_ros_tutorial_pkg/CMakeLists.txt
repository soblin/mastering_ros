cmake_minimum_required(VERSION 3.0.2)
project(pcl_ros_tutorial_pkg)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  pcl_ros
  roscpp
  sensor_msgs
  )

catkin_package(
  CATKIN_DEPENDS pcl_ros roscpp sensor_msgs
  )

include_directories(
  ${catkin_INCLUDE_DIRS}
  )

add_executable(pcl_publisher_node src/pcl_publisher.cpp)
add_executable(pcl_filter src/pcl_filter.cpp)
add_executable(pcl_write src/pcl_write.cpp)
add_executable(pcl_read src/pcl_read.cpp)

target_link_libraries(pcl_publisher_node
  ${catkin_LIBRARIES}
  )

target_link_libraries(pcl_filter
  ${catkin_LIBRARIES}
  )

target_link_libraries(pcl_write
  ${catkin_LIBRARIES}
  )

target_link_libraries(pcl_read
  ${catkin_LIBRARIES}
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
