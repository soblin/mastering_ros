#ifndef MY_CONTROLLER_FILE_H
#define MY_CONTROLLER_FILE_H

#include <pr2_controller_interface/controller.h>
#include <pr2_mechanism_model/joint.h>

namespace my_controller_ns{

class MyControllerClass : public pr2_controller_interface::Controller{
 public:
  virtual bool init(pr2_mechanism_model::RobotState *robot, ros::NodeHandle &nh) override;
  virtual void starting() override;
  virtual void update() override;
  virtual void stopping() override;
  
 private:
  pr2_mechanism_model::JointState *joint_state_ptr_;
  double init_pos_;
};

} // namespace my_controller_ns

#endif /* MY_CONTROLLER_FILE_H */
