#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/filters/voxel_grid.h>

class CloudHandler
{
public:
  CloudHandler()
  {
    pcl_sub_ = nh_.subscribe("pcl_output", 10, &CloudHandler::cloudCB, this);
    pcl_pub_ = nh_.advertise<sensor_msgs::PointCloud2>("pcl_filtered", 1);
  }
  void cloudCB(const sensor_msgs::PointCloud2& input)
  {
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::PointCloud<pcl::PointXYZ> cloud_filtered;
    sensor_msgs::PointCloud2 output;

    pcl::fromROSMsg(input, cloud);

    pcl::VoxelGrid<pcl::PointXYZ> vox_obj;
    vox_obj.setInputCloud(cloud.makeShared());

    vox_obj.setLeafSize(0.1f, 0.1f, 0.1f);

    vox_obj.filter(cloud_filtered);

    pcl::toROSMsg(cloud_filtered, output);
    output.header.frame_id = "point_cloud";

    pcl_pub_.publish(output);
  }

private:
  ros::NodeHandle nh_;
  ros::Publisher pcl_pub_;
  ros::Subscriber pcl_sub_;
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pcl_filter");

  ROS_INFO("Started Filter Node");

  CloudHandler hanlder;

  ros::spin();

  return 0;
}
