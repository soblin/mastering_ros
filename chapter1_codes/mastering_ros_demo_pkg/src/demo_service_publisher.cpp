#include <vector>

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/UInt32.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>

#include <mastering_ros_demo_pkg/unit.h>
#include <mastering_ros_demo_pkg/full_message.h>

int main(int argc, char **argv){
    ros::init(argc, argv, "demo_service_publisher_node");
    ros::NodeHandle node_obj;
    ros::Publisher demo_service_publisher_node = node_obj.advertise<mastering_ros_demo_pkg::full_message>("/demo_service_publisher_topic", 10);
    
    ros::Rate loop_rate(10);

    mastering_ros_demo_pkg::full_message msg;
    mastering_ros_demo_pkg::unit unit_msg;

    std::vector<std::string> greetings1 = {"abcd", "efg", "hijk", "lmn"};
    std::vector<std::string> greetings2 = {"opqr", "stu", "vw", "xyz"};
    
    while(ros::ok()){
        
    }
}
