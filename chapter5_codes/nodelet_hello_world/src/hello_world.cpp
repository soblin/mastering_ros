#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <stdio.h>

namespace nodelet_hello_world
{
class Hello : public nodelet::Nodelet
{
public:
  virtual void onInit() override;
  void callback(const std_msgs::StringConstPtr input);

private:
  ros::Publisher pub_;
  ros::Subscriber sub_;
};

void Hello::onInit()
{
  ros::NodeHandle& private_nh = getPrivateNodeHandle();
  NODELET_DEBUG("Initialized the Nodelet");
  pub_ = private_nh.advertise<std_msgs::String>("msg_out", 5);
  sub_ = private_nh.subscribe("msg_in", 5, &Hello::callback, this);
}

void Hello::callback(const std_msgs::StringConstPtr input)
{
  std_msgs::String output;
  output.data = input->data;

  NODELET_DEBUG("Message data = %s", output.data.c_str());
  ROS_INFO("Message data = %s", output.data.c_str());
  pub_.publish(output);
}

}  // namespae nodelet_hello_world

PLUGINLIB_EXPORT_CLASS(nodelet_hello_world::Hello, nodelet::Nodelet);
