#include <cstdint>
#include <sstream>

#include <ros/ros.h>

#include <mastering_ros_demo_pkg/data.h>
#include <mastering_ros_demo_pkg/data_array.h>

/*
 * data format as follows
 * array_msg = 
 *[{int32, int32, string, string}
 *, .............................
 *, .............................
 *, (variable length)
 *,{int32, int32, string, string}
 *]
 */
int main(int argc, char **argv){
    ros::init(argc, argv, "array_msg_publisher_node");
    ros::NodeHandle node_obj;
    ros::Publisher array_msg_publisher_node = node_obj.advertise<mastering_ros_demo_pkg::data_array>("/array_msg_publisher_topic", 50);

    ros::Rate loop_rate(1);

    mastering_ros_demo_pkg::data_array array_msg;
    mastering_ros_demo_pkg::data data_msg;

    //順番にサイズ2, 5の配列を送ってみる
    int32_t upper_left, lower_right;
    std::string color, camera_id;
    //1st try
    upper_left = 500; lower_right = 100;
    color =  "red"; camera_id = "No.100";
    data_msg.lowerRight = lower_right;
    data_msg.upperLeft = upper_left;
    data_msg.color = color.c_str();
    data_msg.cameraID = camera_id.c_str();
    array_msg.img_data.push_back(data_msg);

    upper_left = 300; lower_right = 200;
    color = "blue"; camera_id = "No.200";
    data_msg.lowerRight = lower_right;
    data_msg.upperLeft = upper_left;
    data_msg.color = color.c_str();
    data_msg.cameraID = camera_id.c_str();
    array_msg.img_data.push_back(data_msg);
    //送る
    array_msg_publisher_node.publish(array_msg);
    ros::spinOnce();
    loop_rate.sleep();

    array_msg.img_data.clear();
    //2nd try
    upper_left = 100; lower_right = 100;
    color = "red"; camera_id = "No.100";
    data_msg.lowerRight = lower_right;
    data_msg.upperLeft = upper_left;
    data_msg.color = color.c_str();
    data_msg.cameraID = camera_id.c_str();
    array_msg.img_data.push_back(data_msg);

    upper_left = 200; lower_right = 200;
    color = "blue"; camera_id = "No.200";
    data_msg.lowerRight = lower_right;
    data_msg.upperLeft = upper_left;
    data_msg.color = color.c_str();
    data_msg.cameraID = camera_id.c_str();
    array_msg.img_data.push_back(data_msg);

    upper_left = 300; lower_right = 300;
    color = "yellow"; camera_id = "No.300";
    data_msg.lowerRight = lower_right;
    data_msg.upperLeft = upper_left;
    data_msg.color = color.c_str();
    data_msg.cameraID = camera_id.c_str();
    array_msg.img_data.push_back(data_msg);

    upper_left =400; lower_right = 400;
    color = "pink"; camera_id = "No.400";
    data_msg.lowerRight = lower_right;
    data_msg.upperLeft = upper_left;
    data_msg.color = color.c_str();
    data_msg.cameraID = camera_id.c_str();
    array_msg.img_data.push_back(data_msg);

    upper_left = 500; lower_right = 500;
    color = "green"; camera_id = "No.500";
    data_msg.lowerRight = lower_right;
    data_msg.upperLeft = upper_left;
    data_msg.color = color.c_str();
    data_msg.cameraID = camera_id.c_str();
    array_msg.img_data.push_back(data_msg);

    array_msg_publisher_node.publish(array_msg);
    ros::spinOnce();
    loop_rate.sleep();

    return 0;
}
