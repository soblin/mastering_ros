#include <my_controller_pkg/my_controller_file.h>
#include <pluginlib/class_list_macros.h>

namespace my_controller_ns
{
bool MyControllerClass::init(pr2_mechanism_model::RobotState* robot, ros::NodeHandle& nh)
{
  std::string joint_name;
  if (!nh.getParam("joint_name", joint_name))
  {
    ROS_ERROR("No joint given in namepsace: '%s'", nh.getNamespace().c_str());
    return false;
  }

  joint_state_ptr_ = robot->getJointState(joint_name);
  if (!joint_state_ptr_)
  {
    ROS_ERROR("MyController could not find joint name '%s'", joint_name.c_str());
    return false;
  }
  return true;
}

void MyControllerClass::starting()
{
  init_pos_ = joint_state_ptr_->position_;
}

void MyControllerClass::update()
{
  double desired_pos = init_pos_ + 15 * sin(ros::Time::now().toSec());
  double current_pos = joint_state_ptr_->position_;
  joint_state_ptr_->commanded_effort_ = -10 * (current_pos - desired_pos);
}

void MyControllerClass::stopping()
{
  return;
}

}  // namespace my_controller_ns

PLUGINLIB_EXPORT_CLASS(my_controller_ns::MyControllerClass, pr2_controller_interface::Controller);
