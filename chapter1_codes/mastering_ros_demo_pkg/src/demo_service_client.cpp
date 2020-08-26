#include <ros/ros.h>
#include <std_msgs/Int32.h>

#include <mastering_ros_demo_pkg/demo_service.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "demo_service_client_node");
  ros::NodeHandle node_obj;
  ros::ServiceClient demo_service_client_node =
      node_obj.serviceClient<mastering_ros_demo_pkg::demo_service>("demo_service_server_service");

  ros::Rate loop_rate(10);
  int counter = 1;
  while (ros::ok())
  {
    mastering_ros_demo_pkg::demo_service srv;
    srv.request.number = counter;
    if (demo_service_client_node.call(srv))
      ROS_INFO("%s", srv.response.nabeatsu.c_str());
    else
    {
      ROS_ERROR("Failed to connect to nabeatsu-server");
      return 1;
    }
    ros::spinOnce();
    loop_rate.sleep();
    counter += 1;
  }
  return 0;
}
