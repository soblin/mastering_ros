#include <ros/ros.h>
#include <std_msgs/UInt32.h>

void callback(const std_msgs::UInt32::ConstPtr& msg)
{
  ROS_INFO("received %d", msg->data);
}
int main(int argc, char** argv)
{
  ros::init(argc, argv, "demo_topic_subscriber_node");
  ros::NodeHandle node_obj;
  ros::Subscriber demo_topic_subscriber_node = node_obj.subscribe("/demo_topic_publisher_topic", 10, callback);
  ros::spin();
  return 0;
}
