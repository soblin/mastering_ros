#include <cstdint>
#include <sstream>

#include <ros/ros.h>

#include <mastering_ros_demo_pkg/data.h>
#include <mastering_ros_demo_pkg/data_array.h>

/*
  data format as follows
  array_msg =
  [{int32, int32, string, string}
  , .............................
  , .............................
  , (variable length)
  ,{int32, int32, string, string}
  ]
*/

using pkg_data = mastering_ros_demo_pkg::data;
using pkg_data_array = mastering_ros_demo_pkg::data_array;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "array_msg_publisher_node");
  ros::NodeHandle node_obj;
  ros::Publisher array_msg_publisher_node = node_obj.advertise<pkg_data_array>("/array_msg_publisher_topic", 50);

  ros::Rate loop_rate(1);

  pkg_data_array array_msg;
  pkg_data data_msg;

  auto packData = [](pkg_data& data, int32_t upper_left, int32_t lower_right, const char* color,
                     const char* camera_id) {
    data.upperLeft = upper_left;
    data.lowerRight = lower_right;
    data.color = std::string(color);
    data.cameraID = std::string(camera_id);
  };

  // 1st try
  packData(data_msg, 500, 100, "red", "No.100");
  array_msg.img_data.push_back(data_msg);

  packData(data_msg, 300, 200, "blue", "No.200");
  array_msg.img_data.push_back(data_msg);
  // send
  array_msg_publisher_node.publish(array_msg);
  ros::spinOnce();
  loop_rate.sleep();
  array_msg.img_data.clear();

  // 2nd try
  packData(data_msg, 100, 100, "red", "No.100");
  array_msg.img_data.push_back(data_msg);

  packData(data_msg, 200, 200, "blue", "No.200");
  array_msg.img_data.push_back(data_msg);

  packData(data_msg, 300, 300, "yellow", "No.200");
  array_msg.img_data.push_back(data_msg);

  packData(data_msg, 400, 400, "pink", "No.400");
  array_msg.img_data.push_back(data_msg);

  packData(data_msg, 500, 500, "green", "No.500");
  array_msg.img_data.push_back(data_msg);

  array_msg_publisher_node.publish(array_msg);
  ros::spinOnce();
  loop_rate.sleep();

  return 0;
}
