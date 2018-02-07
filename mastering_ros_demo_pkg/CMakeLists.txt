cmake_minimum_required(VERSION 2.8.3)

project(mastering_ros_demo_pkg)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  roscpp
  std_msgs
  #msgとsrvからデータ型を自動生成
  #catkin_ws/devel/include/mastering_ros_demo_pkg/demo_msg.hを作ってくれる
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
  )

add_service_files(
  FILES
  demo_service.srv
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

#add_dependencies(ノード名 パッケージ名_generate_messages_cpp)とかく
add_dependencies(demo_topic_publisher_node  mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(demo_topic_subscriber_node mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(demo_msg_publisher_node    mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(demo_msg_subscriber_node   mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(demo_service_server_node   mastering_ros_demo_pkg_generate_messages_cpp)
add_dependencies(demo_service_client_node   mastering_ros_demo_pkg_generate_messages_cpp)

target_link_libraries(demo_topic_publisher_node  ${catkin_LIBRARIES})
target_link_libraries(demo_topic_subscriber_node ${catkin_LIBRARIES})
target_link_libraries(demo_msg_publisher_node    ${catkin_LIBRARIES})
target_link_libraries(demo_msg_subscriber_node   ${catkin_LIBRARIES})
target_link_libraries(demo_service_server_node   ${catkin_LIBRARIES})
target_link_libraries(demo_service_client_node   ${catkin_LIBRARIES})
