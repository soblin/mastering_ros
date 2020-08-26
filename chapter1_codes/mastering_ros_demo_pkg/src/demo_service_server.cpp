#include <sstream>

#include <ros/ros.h>

#include <mastering_ros_demo_pkg/demo_service.h>

bool nabeatsu(const int num)
{
  if (num % 3 == 0)
    return true;
  else
  {
    std::string str = std::to_string(num);
    if (str.find('3') == std::string::npos)
    {
      return false;
    }
    return true;
  }
}

bool callback(mastering_ros_demo_pkg::demo_service::Request& req, mastering_ros_demo_pkg::demo_service::Response& res)
{
  std::stringstream ss;
  int number = req.number;
  if (nabeatsu(number))
  {
    ss << std::to_string(number) + "!!!!!!!!!!!";
  }
  else
    ss << std::to_string(number) + " is a trivial number";

  res.nabeatsu = ss.str();

  return true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "demo_service_server_node");
  ros::NodeHandle node_obj;

  ros::ServiceServer demo_service_server_node = node_obj.advertiseService("demo_service_server_service", callback);
  ROS_INFO("The server is ready");
  ros::spin();

  return 0;
}
