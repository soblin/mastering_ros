cmake_minimum_required(VERSION 3.0.2)
project(rviz_teleop_commander)

add_compile_options(-std=c++11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rviz
  std_msgs
  )

catkin_package()

set(CMAKE_AUTOMOC ON)
find_package(Qt5 ${rviz_QT_VERSION} EXACT REQUIRED
  Core
  Widgets
  )
set(QT_LIBRARIES Qt5::Widgets)
add_definitions(-DQT_NO_KEYWORDS)

include_directories(
  ${catkin_INCLUDE_DIRS}
  )

link_directories(${catkin_LIBRARY_DIRS})

add_library(${PROJECT_NAME}
  src/teleop_pad.cpp
  )

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${QT_LIBRARIES}
  )

install(TARGETS
  ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )

install(FILES
  plugin_description.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
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
