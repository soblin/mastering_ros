#include <actionlib/server/simple_action_server.h>
#include <fibonacci_action/FibonacciAction.h>
#include <ros/ros.h>

class FibonacciAction
{
protected:
  ros::NodeHandle node_handle_;
  actionlib::SimpleActionServer<fibonacci_action::FibonacciAction> action_server_;
  const std::string name_;
  fibonacci_action::FibonacciFeedback feedback_;
  fibonacci_action::FibonacciResult result_;

public:
  FibonacciAction(const std::string name);
  void executeCallback(const fibonacci_action::FibonacciGoalConstPtr& goal);
};

FibonacciAction::FibonacciAction(const std::string name)
  : action_server_(node_handle_, name, boost::bind(&FibonacciAction::executeCallback, this, _1), false), name_(name)
{
  action_server_.start();
}

void FibonacciAction::executeCallback(const fibonacci_action::FibonacciGoalConstPtr& goal)
{
  ros::Rate rate(1);
  bool success = true;

  // substitute the inital condition a[0]=0, a[1]=1,
  feedback_.sequence.clear();
  feedback_.sequence.push_back(0);
  feedback_.sequence.push_back(1);

  ROS_INFO("%s: Executing. Creating Fibonacci sequence of order %d with seeds "
           "%d, %d",
           name_.c_str(), goal->order, feedback_.sequence[0], feedback_.sequence[1]);

  for (int i = 1; i <= goal->order; i++)
  {
    // check that preemption is not required by the client
    if (action_server_.isPreemptRequested() || !ros::ok())
    {
      ROS_INFO("%s is preempted", name_.c_str());
      action_server_.setPreempted();
      success = false;
      break;
    }
    feedback_.sequence.push_back(feedback_.sequence[i - 1] + feedback_.sequence[i]);
    action_server_.publishFeedback(feedback_);
    rate.sleep();
  }
  if (success)
  {
    result_.sequence = feedback_.sequence;
    ROS_INFO("%s succeeded", name_.c_str());
    action_server_.setSucceeded(result_);
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "fibonacci_server_node");
  FibonacciAction server(ros::this_node::getName());
  ros::spin();

  return 0;
}
