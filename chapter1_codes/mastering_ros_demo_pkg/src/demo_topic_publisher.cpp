#include <ros/ros.h>
#include <std_msgs/UInt32.h>

int main(int argc, char **argv){
    ros::init(argc, argv, "demo_topic_publisher_node");
    ros::NodeHandle node_obj;
    ros::Publisher demo_topic_publisher_node = node_obj.advertise<std_msgs::UInt32>("/demo_topic_publisher_topic", 10);
    ros::Rate loop_rate(10);
    int counter = 0;
    std_msgs::UInt32 send_msg; 
    while(ros::ok()){
        send_msg.data = counter;
        demo_topic_publisher_node.publish(send_msg);
        //wait for the designated time
        ros::spinOnce();
        loop_rate.sleep();
        counter += 1;
    }
    return 0;
}
