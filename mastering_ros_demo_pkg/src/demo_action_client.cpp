#include <iostream>

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <mastering_ros_demo_pkg/demo_actionAction.h>

int main(int argc, char **argv){
    ros::init(argc, argv, "demo_action_client_node");

    if(argc != 3){
        ROS_INFO("%d", argc);
        ROS_WARN("Usage: demo_action_client <goal> <time_to_preempt_in_sec>");
        return 1;
    }

    actionlib::SimpleActionClient<mastering_ros_demo_pkg::demo_actionAction> action_client_("demo_action_server_node", true);

    ROS_INFO("Waiting for action server to start.");

    action_client_.waitForServer();

    ROS_INFO("Action Server Started, sending goal");

    mastering_ros_demo_pkg::demo_actionGoal goal;
    goal.goal_deg = atoi(argv[1]);

    ROS_INFO("Sending goal [%d] and Preempt time of [%d]", goal.goal_deg, atoi(argv[2]));
    action_client_.sendGoal(goal);

    bool finished_before_timeout = action_client_.waitForResult(ros::Duration(atoi(argv[2])));
    action_client_.cancelGoal();

    if(finished_before_timeout){
        actionlib::SimpleClientGoalState state = action_client_.getState();
        ROS_INFO("Action finished: %s", state.toString().c_str());
        action_client_.cancelGoal();
    }
    else{
        ROS_INFO("Action did not finish before the timeout");
    }

    return 0;
}
