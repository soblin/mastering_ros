cmake_minimum_required(VERSION 2.8.3)
project(pluginlib_calculator)

add_compile_options(-std=c++11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED COMPONENTS
  pluginlib
  roscpp
  std_msgs
  )

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES pluginlib_calculator
  CATKIN_DEPENDS pluginlib roscpp std_msgs
  DEPENDS system_lib
  )

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  )

add_library(pluginlib_calculator lib/CalculatorPlugins.cpp)
target_link_libraries(pluginlib_calculator ${catkin_LIBRARIES})

add_executable(calculator_loader_node src/calculator_loader.cpp)
target_link_libraries(calculator_loader_node ${catkin_LIBRARIES})

install(TARGETS pluginlib_calculator calculator_loader_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
  )

### Mark other files for installation (e.g. launch and bag files, etc.)
install(FILES
  calculator_plugins.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )

file(GLOB srcs
  "include/pluginlib_calculator/*"
  "lib/*"
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
