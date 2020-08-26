#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Time.h>

#include <mastering_ros_demo_pkg/self.h>

void callback(const mastering_ros_demo_pkg::self::ConstPtr msg)
{
  ROS_INFO("name: %s, age: %d, time: %u", msg->name.c_str(), msg->age, msg->cur_time.sec);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "self_msg_subscriber_node");
  ros::NodeHandle node_handle;
  ros::Subscriber self_msg_subscriber_node =
      node_handle.subscribe<mastering_ros_demo_pkg::self>("/self_msg_publisher_topic", 50, callback);
  ros::spin();
  return 0;
}
