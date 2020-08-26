#include <actionlib/server/simple_action_server.h>
#include <cmath>
#include <random>
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <vector>

#include <averaging_action/AveragingAction.h>

static void stat(const std::vector<double>& arr, double& mean, double& std_dev)
{
  int N = arr.size();
  double sum = 0;
  for (int i = 0; i < N; ++i)
    sum += arr[i];

  mean = sum / N;
  double var = 0;
  for (int i = 0; i < N; ++i)
    var += std::pow(arr[i] - mean, 2);

  std_dev = std::sqrt(var / N);
}

class AveragingAction
{
protected:
  ros::NodeHandle node_handle_;
  actionlib::SimpleActionServer<averaging_action::AveragingAction> action_server_;

  averaging_action::AveragingFeedback feedback_;
  averaging_action::AveragingResult result_;

  const std::string name_;
  int data_count_ = 0;

  double mean_ = 0;
  double sdv_ = 0;
  std::random_device seed_gen_;
  std::default_random_engine engine_;
  std::uniform_real_distribution<> dist_;
  std::vector<double> vals_;

public:
  AveragingAction(std::string name)
    : action_server_(node_handle_, name, boost::bind(&AveragingAction::executeCB, this, _1), false)
    , name_(name)
    , engine_(seed_gen_())
  {
    // set limit
    std::uniform_real_distribution<>::param_type param(0.0, 1.0);
    dist_.param(param);
    // start server
    action_server_.registerPreemptCallback(boost::bind(&AveragingAction::preemptCallback, this));
    action_server_.start();
  }

  void executeCB(const averaging_action::AveragingGoalConstPtr& goal)
  {
    if (!action_server_.isActive() or action_server_.isPreemptRequested())
      return;

    ros::Rate rate(5);

    const int sample_number_goal = goal->sample_number;
    if (data_count_ >= sample_number_goal)
    {
      ROS_INFO("already generated %d numbers, returning to zero", sample_number_goal);
      clearAll();
      action_server_.setSucceeded(result_);
      return;
    }

    while (data_count_ <= sample_number_goal)
    {
      if (!ros::ok())
      {
        action_server_.setAborted(result_, "I failed!");
        ROS_INFO("%s is shutting down", name_.c_str());
        break;
      }

      if (!action_server_.isActive() or action_server_.isPreemptRequested())
        return;

      if (data_count_ >= sample_number_goal)
      {
        ROS_INFO("%s finished cmd", name_.c_str());
        result_.mean = mean_;
        result_.std_dev = sdv_;
        action_server_.setSucceeded(result_);
        clearAll();
        return;
      }

      // main operation
      else
      {
        double val = dist_(engine_);
        vals_.push_back(val);
        data_count_ += 1;
        stat(vals_, mean_, sdv_);
        feedback_.sample = data_count_;
        feedback_.data = val;
        feedback_.mean = mean_;
        feedback_.std_dev = sdv_;
        ROS_INFO("mean = %f, sdv = %f", mean_, sdv_);
        action_server_.publishFeedback(feedback_);
      }

      rate.sleep();
    }
  }

  void preemptCallback()
  {
    ROS_WARN("%s got preempted!", name_.c_str());
    result_.mean = result_.std_dev = 0;
    action_server_.setPreempted(result_, "I got preempted");
  };

  void clearAll()
  {
    vals_.clear();
    data_count_ = 0;
    mean_ = sdv_ = 0;
    result_.mean = result_.std_dev = 0;
    feedback_.sample = feedback_.data = feedback_.mean = feedback_.std_dev = 0;
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "averaging_action_server_node");
  AveragingAction ac(ros::this_node::getName());
  ros::spin();
  return 0;
}
