#include <iostream>
#include <sstream>

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <std_msgs/Int32.h>

#include <mastering_ros_demo_pkg/demo_actionAction.h>

class demo_actionAction{
protected:
    ros::NodeHandle node_obj;
    /*demo_action_server_node
     * NodeHandle instance must be created before this line.
     * Otherwise strange error may occur.
     */
    actionlib::SimpleActionServer<mastering_ros_demo_pkg::demo_actionAction> demo_action_server_node;
    mastering_ros_demo_pkg::demo_actionFeedback feedback;
    mastering_ros_demo_pkg::demo_actionResult result;

    std::string action_name;
    int goal;
    int progress;

public:
    demo_actionAction(std::string name):
        demo_action_server_node(node_obj, name, boost::bind(&demo_actionAction::executeCB, this, _1), false),
        action_name(name)
    {
        demo_action_server_node.registerPreemptCallback(boost::bind(&demo_actionAction::preemptCB, this));
        demo_action_server_node.start();
    }

    ~demo_actionAction(void){};

    void preemptCB(){
        ROS_WARN("%s got preempted!", action_name.c_str());
        result.final_deg = progress;
        demo_action_server_node.setPreempted(result, "I got preempted");
    }

    void executeCB(const mastering_ros_demo_pkg::demo_actionGoalConstPtr &goal){
        if(!demo_action_server_node.isActive() || demo_action_server_node.isPreemptRequested()) return;
        ros::Rate rate(5);
        ROS_INFO("%s is processing the goal %d", action_name.c_str(), goal->goal_deg);
        for(progress=1; progress<=goal->goal_deg; progress++){
            if(!ros::ok()){
                result.final_deg = progress;
                demo_action_server_node.setAborted(result, "I failed");
                ROS_INFO("%s shutting down", action_name.c_str());
                break;
            }
            if(!demo_action_server_node.isActive() || demo_action_server_node.isPreemptRequested()) return;
            if(goal->goal_deg <= progress){
                ROS_INFO("%s succeeded in getting to goal %d", action_name.c_str(), goal->goal_deg);
                result.final_deg = progress;
                demo_action_server_node.setSucceeded(result);
            }
            else{
                ROS_INFO("setting to goal %d / %d", feedback.current_deg, goal->goal_deg);
                feedback.current_deg = progress;
                demo_action_server_node.publishFeedback(feedback);
            }
            rate.sleep();
        }
    }
};

int main(int argc, char**argv){
    ros::init(argc, argv, "demo_action_server_node");
    ROS_INFO("Starting Demo Action Server");
    demo_actionAction demo_action_obj(ros::this_node::getName());
    ros::spin();
    return 0;
}
