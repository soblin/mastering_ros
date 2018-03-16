#include <vector>
#include <cstdint>

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/UInt32.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>

#include <mastering_ros_demo_pkg/unit.h>
#include <mastering_ros_demo_pkg/full_message.h>

/*
 *--- data format ---
msg = 

[{str, int, uint, str, float, bool}
,{str, int, uint, str, float, bool}
,{str, int, uint, str, float, bool}
,{str, int, uint, str, float, bool}
]

*/
int main(int argc, char **argv){
    ros::init(argc, argv, "demo_msg_publisher_node");
    ros::NodeHandle node_obj;
    ros::Publisher demo_msg_publisher_node = node_obj.advertise<mastering_ros_demo_pkg::full_message>("/demo_msg_publisher_topic", 50);
    
    ros::Rate loop_rate(100000);

    mastering_ros_demo_pkg::full_message msg;
    mastering_ros_demo_pkg::unit unit_msg;

    //送るメッセージの内容
    std::vector<std::string> greetings1 = {"abcd", "efg", "hijk", "lmn"};
    std::vector<std::string> greetings2 = {"opqr", "stu", "vw", "xyz"};
    int32_t number = 0;
    uint32_t unumber = 0;
    float fnumber = 0.5;
    bool TrueOrFalse = true;
    
    while(ros::ok()){
        //送るデータをunit_msgに詰める->msgにpush_backを4回やって配列にして送る
        for(int i=0; i<4; i++){
            unit_msg.greeting1 = greetings1[i];
            unit_msg.number = number++;
            unit_msg.unumber = unumber++;
            unit_msg.greeting2 = greetings2[i];
            unit_msg.fnumber = fnumber++;
            unit_msg.TrueOfFalse = TrueOrFalse;
            TrueOrFalse = !TrueOrFalse;

            msg.messages.push_back(unit_msg);
        }

        demo_msg_publisher_node.publish(msg);

        //adjust the period
        ros::spinOnce();
        loop_rate.sleep();
        
    }

    return 0;
}
