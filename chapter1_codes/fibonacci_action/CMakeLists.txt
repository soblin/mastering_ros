cmake_minimum_required(VERSION 2.8.3)
project(fibonacci_action)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  roscpp
  std_msgs
)

find_package(Boost REQUIRED COMPONENTS)

add_action_files(
  FILES
  Fibonacci.action
  )

generate_messages(
  DEPENDENCIES
  actionlib_msgs
  std_msgs
  )

catkin_package(
  CATKIN_DEPENDS actionlib actionlib_msgs roscpp std_msgs
  )

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(fibonacci_server_node src/fibonacci_server.cpp)
add_executable(fibonacci_client_node src/fibonacci_client.cpp)

add_dependencies(fibonacci_server_node fibonacci_action_generate_messages_cpp)
add_dependencies(fibonacci_client_node fibonacci_action_generate_messages_cpp)

target_link_libraries(fibonacci_server_node ${catkin_LIBRARIES})
target_link_libraries(fibonacci_client_node ${catkin_LIBRARIES})

file(GLOB srcs
  "src/*"
  )

find_program(CLANG_FORMAT_EXE clang-format)
if(CLANG_FORMAT_EXE)
  add_custom_target(${PROJECT_NAME}-format ALL
    COMMAND clang-format --style=file -i ${srcs}
    COMMENT "Running clang-format in ${PROJECT_NAME}"
    VERBATIM
    )
endif()
