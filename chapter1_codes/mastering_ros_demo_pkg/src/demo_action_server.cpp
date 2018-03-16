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
    mastering_ros_demo_pkg::demo_actionFeedback feedback_;
    mastering_ros_demo_pkg::demo_actionResult result_;
 
    const std::string action_name_;
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
        result_.final_deg = progress_;
        action_server_.setPreempted(result_, "I got preempted");
    }

    /*
     * This is the callback function to execute when the client does sendGoal(goal) and this server received the goal value.
     * let action file be actionName.action
     * format : executeCB(const package::"actionName${ConstPtr}" &goal)
     */
    void executeCallback(const mastering_ros_demo_pkg::demo_actionGoalConstPtr &goal){
        if(!action_server_.isActive() || action_server_.isPreemptRequested()) return;
        ros::Rate rate(5);
        ROS_INFO("%s is progressing the goal %d", action_name_.c_str(), goal->goal_deg);
        for(progress_ = 1; progress_ <= goal->goal_deg; progress_++ ){
            /*
             * if something is wrong
             */
            if(!ros::ok()){
                result_.final_deg = progress_;
                action_server_.setAborted(result_, "I failed!");
                ROS_INFO("%s shutting down", action_name_.c_str());
                break;
            }

            if(!action_server_.isActive() || action_server_.isPreemptRequested()) return;

            if(goal->goal_deg <= progress_){
                ROS_INFO("%s succeeded in getting to goal %d", action_name_.c_str(), goal->goal_deg);
                result_.final_deg = progress_;
                action_server_.setSucceeded(result_);
            }
            /*
             * main operation
             */
            else{
                ROS_INFO("setting to goal %d / %d", feedback_.current_deg, goal->goal_deg);
                feedback_.current_deg = progress_;
                action_server_.publishFeedback(feedback_);
            }
            rate.sleep();
        }
    }
};

int main(int argc, char **argv){
    /*
     * The third argument is used for the client to connect to this server.
     * You need to use the same name(in this case "demo_action_server_node") in the client program as follows.
     * actionlib::SimpleActionClient<$packageName::$actionName"Action">:: action_client_("demo_action_server_node", true/false)
     */
    ros::init(argc, argv, "demo_action_server_node");
    ROS_INFO("Starting demo_action server");
    demo_actionAction demo_action_obj(ros::this_node::getName());
    ros::spin();
    return 0;
}
