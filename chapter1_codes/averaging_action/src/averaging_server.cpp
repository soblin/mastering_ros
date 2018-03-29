#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <actionlib/server/simple_action_server.h>

#include <averaging_action/AveragingAction.h>

class AveragingAction{
protected:
    ros::NodeHandle node_handle_;
    actionlib::SimpleActionServer<averaging_action::AveragingAction> action_server_;
    const std::string name_;
    int data_count_, goal_;
    float sum_, sum_sq_;
    averaging_action::AveragingFeedback feedback_;
    averaging_action::AveragingResult result_;
    ros::Subscriber sub_;

public:
    AveragingAction(std::string name):
        action_server_(node_handle_, name, false),
        name_(name)
    {
        action_server_.registerGoalCallback(boost::bind(&AveragingAction::goalCallback, this));
        action_server_.registerPreemptCallback(boost::bind(&AveragingAction::preemptCallback, this));
        sub_ = node_handle_.subscribe<std_msgs::Float32>("/random_number", 1, &AveragingAction::analysisCallback, this);
        action_server_.start();
    }

    void goalCallback();
    void preemptCallback();
    void analysisCallback(const std_msgs::Float32::ConstPtr &msg);
};

int main(){
    return 0;
}
