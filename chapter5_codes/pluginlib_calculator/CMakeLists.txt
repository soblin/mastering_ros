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

## libpluginlib_calculatorを利用するのにcalculator_loader_nodeが必要
add_library(pluginlib_calculator src/calculator_plugins.cpp)
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

## Mark other files for installation (e.g. launch and bag files, etc.)
install(FILES
   # myfile1
   # myfile2
   calculator_plugins.xml
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
   )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_pluginlib_calculator.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
