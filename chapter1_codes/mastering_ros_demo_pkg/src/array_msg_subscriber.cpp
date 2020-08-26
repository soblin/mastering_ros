#include <mastering_ros_demo_pkg/data.h>
#include <mastering_ros_demo_pkg/data_array.h>
#include <ros/ros.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/MultiArrayLayout.h>

void callback(const mastering_ros_demo_pkg::data_array::ConstPtr& msg)
{
  int len = msg->img_data.size();
  ROS_INFO("Received messages of length %d", len);
  for (int i = 0; i < len; i++)
  {
    ROS_INFO("upperLeft:%d, lowerRight:%d, color:%s, cameraID:%s", msg->img_data[i].upperLeft,
             msg->img_data[i].lowerRight, msg->img_data[i].color.c_str(), msg->img_data[i].cameraID.c_str());
  }
  ROS_INFO("That's all.");
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "array_msg_susbcriber_node");
  ros::NodeHandle node_obj;

  ros::Subscriber array_msg_susbcriber_node =
      node_obj.subscribe<mastering_ros_demo_pkg::data_array>("/array_msg_publisher_topic", 50, callback);
  ros::spin();
  return 0;
}
