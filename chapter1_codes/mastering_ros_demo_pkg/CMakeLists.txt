cmake_minimum_required(VERSION 2.8.3)

project(mastering_ros_demo_pkg)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  roscpp
  std_msgs
  # automatically code-gen catkin_ws/devel/include/mastering_ros_demo_pkg/demo_msg.h
  message_generation
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${BOOST_INCLUDE_DIRS}
)

add_message_files(
  FILES
  unit.msg
  full_message.msg
  data.msg
  data_array.msg
  self.msg
  )

add_service_files(
  FILES
  demo_service.srv
  )

add_action_files(
  FILES
  demo_action.action
  )

generate_messages(
  DEPENDENCIES
  std_msgs
  actionlib_msgs
  )

catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs actionlib actionlib_msgs message_runtime
  )

add_executable(demo_topic_publisher_node  src/demo_topic_publisher.cpp)
add_executable(demo_topic_subscriber_node src/demo_topic_subscriber.cpp)
add_executable(demo_msg_publisher_node    src/demo_msg_publisher.cpp)
add_executable(demo_msg_subscriber_node   src/demo_msg_subscriber.cpp)
add_executable(demo_service_server_node   src/demo_service_server.cpp)
add_executable(demo_service_client_node   src/demo_service_client.cpp)
add_executable(demo_action_server_node    src/demo_action_server.cpp)
add_executable(demo_action_client_node    src/demo_action_client.cpp)
add_executable(array_msg_publisher_node   src/array_msg_publisher.cpp)
add_executable(array_msg_subscriber_node  src/array_msg_subscriber.cpp)
add_executable(self_msg_publisher_node    src/self_msg_publisher.cpp)
add_executable(self_msg_subscriber_node   src/self_msg_subscriber.cpp)

# add_dependencies(<node name> <package name>_generate_messages_cpp)
add_dependencies(demo_topic_publisher_node  mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(demo_topic_subscriber_node mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(demo_msg_publisher_node    mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(demo_msg_subscriber_node   mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(demo_service_server_node   mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(demo_service_client_node   mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(demo_action_server_node    mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(demo_action_client_node    mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(array_msg_publisher_node   mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(array_msg_subscriber_node  mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(self_msg_publisher_node    mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(self_msg_subscriber_node   mastering_ros_demo_pkg_generate_messages_cpp)

target_link_libraries(demo_topic_publisher_node  ${catkin_LIBRARIES})
target_link_libraries(demo_topic_subscriber_node ${catkin_LIBRARIES})
target_link_libraries(demo_msg_publisher_node    ${catkin_LIBRARIES})
target_link_libraries(demo_msg_subscriber_node   ${catkin_LIBRARIES})
target_link_libraries(demo_service_server_node   ${catkin_LIBRARIES})
target_link_libraries(demo_service_client_node   ${catkin_LIBRARIES})
target_link_libraries(demo_action_server_node    ${catkin_LIBRARIES})
target_link_libraries(demo_action_client_node    ${catkin_LIBRARIES})
target_link_libraries(array_msg_publisher_node   ${catkin_LIBRARIES})
target_link_libraries(array_msg_subscriber_node  ${catkin_LIBRARIES})
target_link_libraries(self_msg_publisher_node    ${catkin_LIBRARIES})
target_link_libraries(self_msg_subscriber_node   ${catkin_LIBRARIES})

file(GLOB exe_sources
  "src/*"
  )

set(project_sources
  ${exe_sources}
  )
# clang-format
find_program(CLANG_FORMAT_EXE clang-format)
if(CLANG_FORMAT_EXE)
  # run clang-format
  add_custom_target(${PROJECT_NAME}-format ALL
    COMMAND clang-format --style=file -i ${project_sources}
    COMMENT "Running clang-format in ${PROJECT_NAME}"
    VERBATIM)
endif()
