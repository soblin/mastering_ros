#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Time.h>

/* header file for the custom msg */
#include <mastering_ros_demo_pkg/self.h>

/*
 * msg = [string name, int32 age, time cur_time]
 */
int main(int argc, char**argv){
    ros::init(argc, argv, "self_msg_publisher_node");
    ros::NodeHandle node_handle;
    ros::Publisher self_msg_publisher_node = node_handle.advertise<mastering_ros_demo_pkg::self>("/self_msg_publisher_topic", 50);

    ros::Rate loop_rate(1);

    mastering_ros_demo_pkg::self msg;
    std_msgs::Int32 age;
    std::string name = "I am soblin";
    ros::Time current;

    while(ros::ok()){
        msg.age = age.data;
        msg.name = name;
        msg.cur_time = ros::Time::now();

        self_msg_publisher_node.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }
    
    return 0;
}
