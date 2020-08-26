#include <memory>
#include <pluginlib/class_loader.h>
#include <pluginlib_calculator/CalculatorBase.h>
#include <ros/ros.h>

int main(int argc, char **argv) {
  pluginlib::ClassLoader<calculator_base::CalculatorBase> calc_loader(
      "pluginlib_calculator", "calculator_base::CalculatorBase");

  try {
    boost::shared_ptr<calculator_base::CalculatorBase> add =
        calc_loader.createInstance("pluginlib_calculator/CalculatorAdd");
    add->setNumbers(10, 10);
    double result = add->calc();

    ROS_INFO("10 + 10 = %f", result);
  } catch (pluginlib::PluginlibException &ex) {
    ROS_ERROR("The plugin failed to load for some reson. Error: %s", ex.what());
  }

  try {
    boost::shared_ptr<calculator_base::CalculatorBase> sub =
        calc_loader.createInstance("pluginlib_calculator/CalculatorSub");
    sub->setNumbers(20, 10);
    double result = sub->calc();

    ROS_INFO("20 - 10 = %f", result);
  } catch (pluginlib::PluginlibException &ex) {
    ROS_ERROR("The plugin failed to load for some reson. Error: %s", ex.what());
  }

  try {
    boost::shared_ptr<calculator_base::CalculatorBase> mul =
        calc_loader.createInstance("pluginlib_calculator/CalculatorMul");
    mul->setNumbers(10, 10);
    double result = mul->calc();

    ROS_INFO("10 * 10 = %f", result);
  } catch (pluginlib::PluginlibException &ex) {
    ROS_ERROR("The plugin failed to load for some reson. Error: %s", ex.what());
  }

  try {
    boost::shared_ptr<calculator_base::CalculatorBase> div =
        calc_loader.createInstance("pluginlib_calculator/CalculatorDiv");
    div->setNumbers(10, 10);
    double result = div->calc();

    ROS_INFO("10 / 10 = %f", result);
  } catch (pluginlib::PluginlibException &ex) {
    ROS_ERROR("The plugin failed to load for some reson. Error: %s", ex.what());
  }

  try {
    boost::shared_ptr<calculator_base::CalculatorBase> hypot_ =
        calc_loader.createInstance("pluginlib_calculator/CalculatorHypot");
    hypot_->setNumbers(3, 4);
    double result = hypot_->calc();

    ROS_INFO("hypot(3, 4) = %f", result);
  } catch (pluginlib::PluginlibException &ex) {
    ROS_ERROR("The plugin failed to load for some reson. Error: %s", ex.what());
  }

  return 0;
}
