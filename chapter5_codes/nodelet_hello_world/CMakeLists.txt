cmake_minimum_required(VERSION 3.0.2)
project(nodelet_hello_world)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  nodelet
  roscpp
  std_msgs
  )

catkin_package(
  LIBRARIES nodelet_hello_world
  CATKIN_DEPENDS nodelet roscpp std_msgs
  )

include_directories(
  ${catkin_INCLUDE_DIRS}
  )

add_library(nodelet_hello_world
  src/hello_world.cpp
  )

target_link_libraries(nodelet_hello_world
  ${catkin_LIBRARIES}
  )

if(catkin_EXPORTED_LIBRARIES)
  add_dependencies(nodelet_hello_world ${catkin_EXPORTED_LIBRARIES})
endif()

install(TARGETS nodelet_hello_world
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )

install(FILES
  hello_world.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )

file(GLOB srcs
  "src/*"
  )

find_program(CLANG_FORMAT_EXE clang-format)
if(CLANG_FORMAT_EXE)
  # run clang-format
  add_custom_target(${PROJECT_NAME}-format ALL
    COMMAND clang-format --style=file -i ${srcs}
    COMMENT "Running clang-format"
    VERBATIM)
endif()
