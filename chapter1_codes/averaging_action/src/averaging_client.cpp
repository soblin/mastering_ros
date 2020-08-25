#include <iostream>

#include <actionlib/client/simple_action_client.h>
#include <averaging_action/AveragingAction.h>
#include <ros/ros.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "averaging_action_client_node");

  if (argc != 2) {
    ROS_INFO("Usage: rosrun averaging_action_client_node <sample number>");
    return 1;
  }

  actionlib::SimpleActionClient<averaging_action::AveragingAction>
      action_client("averaging_action_server_node", true);

  ROS_INFO("Waiting for action server to start");

  action_client.waitForServer();

  ROS_INFO("Action server started, sending cmd");

  averaging_action::AveragingGoal goal;
  goal.sample_number = atoi(argv[1]);

  action_client.sendGoal(goal);
  bool finished_before_timeout = action_client.waitForResult(ros::Duration(3));
  action_client.cancelGoal();

  if (finished_before_timeout) {
    actionlib::SimpleClientGoalState state = action_client.getState();
    ROS_INFO("action finished: %s", state.toString().c_str());
    action_client.cancelGoal();
  } else {
    ROS_INFO("action did not finish within 100ms");
  }

  return 0;
}
