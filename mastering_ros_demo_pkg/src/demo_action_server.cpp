#include <iostream>
#include <sstream>

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <std_msgs/Int32.h>

#include <mastering_ros_demo_pkg/demo_actionAction.h>

class demo_actionAction{
protected:
    ros::NodeHandle node_handle_;
    actionlib::SimpleActionServer<mastering_ros_demo_pkg::demo_actionAction> action_server_;
    mastering_ros_demo_pkg::demo_actionActionFeedback feedback_;
    mastering_ros_demo_pkg::demo_actionActionResult result_;

    std::string action_name_;
    int goal_;
    int progress_;

public:
    demo_actionAction(std::string name):
        action_server_(node_handle_, name, boost::bind(&demo_actionAction::executeCallback, this, _1), false),
        action_name_(name)
    {
        action_server_.registerPreemptCallback(boost::bind(&demo_actionAction::preemptCallback, this));
        action_server_.start();
    }

    ~demo_actionAction(void){}

    void preemptCallback(){
        ROS_WARN("%s got preempted!", action_name_.c_str());
        result_.result.final_deg = progress_;
        action_server_.setPreempted(result_.result, "I got preempted");
    }

    void executeCallback(const mastering_ros_demo_pkg::demo_actionGoalConstPtr &goal){
        if(!action_server_.isActive() || action_server_.isPreemptRequested()) return;
        ros::Rate rate(5);
        ROS_INFO("%s is progressing the goal %d", action_name_.c_str(), goal->goal_deg);
        for(progress_ = 1; progress_ <= goal->goal_deg; progress_++ ){
            if(!ros::ok()){
                result_.result.final_deg = progress_;
                action_server_.setAborted(result_.result, "I failed!");
                ROS_INFO("%s shutting down", action_name_.c_str());
                break;
            }

            if(!action_server_.isActive() || action_server_.isPreemptRequested()) return;

            if(goal->goal_deg <= progress_){
                ROS_INFO("%s succeeded in getting to goal %d", action_name_.c_str(), goal->goal_deg);
                result_.result.final_deg = progress_;
                action_server_.setSucceeded(result_.result);
            }

            else{
                ROS_INFO("setting to goal %d / %d", feedback_.feedback.current_deg, goal->goal_deg);
                feedback_.feedback.current_deg = progress_;
                action_server_.publishFeedback(feedback_.feedback);
            }
            rate.sleep();
        }
    }
};

int main(int argc, char **argv){
    ros::init(argc, argv, "demo_action_server_node");
    ROS_INFO("Starting demo_actin server");
    demo_actionAction demo_action_obj(ros::this_node::getName());
    ros::spin();
    return 0;
}
