#include <cstdint>
#include <vector>

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <std_msgs/UInt32.h>

#include <mastering_ros_demo_pkg/full_message.h>
#include <mastering_ros_demo_pkg/unit.h>

void callback(const mastering_ros_demo_pkg::full_message::ConstPtr& msg)
{
  ROS_INFO("Received data\n");
  for (int i = 0; i < msg->messages.size(); i++)
  {
    const mastering_ros_demo_pkg::unit& unit_msg = msg->messages[i];
    ROS_INFO("{greeting1:%s, number:%d, unumber:%d, greeting2:%s, fnumber:%f, "
             "TrueOrFalse:%s}\n",
             unit_msg.greeting1.c_str(), unit_msg.number, unit_msg.unumber, unit_msg.greeting2.c_str(),
             unit_msg.fnumber, (unit_msg.TrueOrFalse ? "true" : "false"));
  }
  ROS_INFO("\n\n");
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "demo_msg_subscriber_node");
  ros::NodeHandle node_obj;
  ros::Subscriber demo_msg_subscriber_node =
      node_obj.subscribe<mastering_ros_demo_pkg::full_message>("/demo_msg_publisher_topic", 50, callback);
  ros::spin();
  return 0;
}
