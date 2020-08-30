#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pcl_publisher");

  ROS_INFO("Started PCL publishing node");

  ros::NodeHandle nh;
  ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2>("pcl_output", 1);
  pcl::PointCloud<pcl::PointXYZ> cloud;
  sensor_msgs::PointCloud2 output;

  cloud.width = 50000;
  cloud.height = 2;
  cloud.points.resize(cloud.width * cloud.height);

  for (size_t i = 0; i < cloud.points.size(); ++i)
  {
    cloud.points[i].x = 512 * rand() / (RAND_MAX + 1.0f);
    cloud.points[i].y = 512 * rand() / (RAND_MAX + 1.0f);
    cloud.points[i].z = 512 * rand() / (RAND_MAX + 1.0f);
  }

  pcl::toROSMsg(cloud, output);
  output.header.frame_id = "point_cloud";

  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    pcl_pub.publish(output);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
