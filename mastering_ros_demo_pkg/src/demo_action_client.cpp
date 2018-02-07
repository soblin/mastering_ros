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

    actionlib::SimpleActionClient<mastering_ros_demo_pkg::demo_actionAction> ac("demo_action", true);

    ROS_INFO("Waiting for action server to start");

    ac.waitForServer();

    ROS_INFO("Action server started, sending goal");

    mastering_ros_demo_pkg::demo_actionGoal goal;
    goal.goal_deg = atoi(argv[1]);

    ROS_INFO("Sending Goal [%d] and preempt time of [%d]", goal.goal_deg, atoi(argv[2]));
    ac.sendGoal(goal);

    bool finished_before_timeout = ac.waitForResult(ros::Duration(atoi(argv[2])));

    ac.cancelGoal();

    if(finished_before_timeout){
        actionlib::SimpleClientGoalState state = ac.getState();
        ac.cancelGoal();
    }
    else{
        ROS_INFO("Action did not finished before the timeout");

    }
    
    return 0;
}
