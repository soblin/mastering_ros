#include <actionlib/client/simple_action_client.h>
#include <fibonacci_action/FibonacciAction.h>
#include <ros/ros.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "fibonacci_client_node");

  actionlib::SimpleActionClient<fibonacci_action::FibonacciAction>
      action_client_("fibonacci_server_node", true);

  // wait for the sepcified server(=fibonacci_server_node).
  action_client_.waitForServer();
  fibonacci_action::FibonacciGoal goal;
  goal.order = 20;
  action_client_.sendGoal(goal);

  bool finished_before_timeout =
      action_client_.waitForResult(ros::Duration(30.0));

  if (finished_before_timeout) {
    actionlib::SimpleClientGoalState state = action_client_.getState();
    ROS_INFO("Action finished: %s", state.toString().c_str());
  } else {
    ROS_INFO("Action did not finish before time out");
  }
  return 0;
}
