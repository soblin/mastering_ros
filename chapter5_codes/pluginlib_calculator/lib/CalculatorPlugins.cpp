#include <cmath>
#include <pluginlib_calculator/CalculatorPlugins.h>

namespace calculator_plugins {

void CalculatorAdd::setNumbers(double number1, double number2) {
  number1_ = number1;
  number2_ = number2;
}

double CalculatorAdd::calc() const { return number1_ + number2_; }

void CalculatorSub::setNumbers(double number1, double number2) {
  number1_ = number1;
  number2_ = number2;
}

double CalculatorSub::calc() const { return number1_ - number2_; }

void CalculatorMul::setNumbers(double number1, double number2) {
  number1_ = number1;
  number2_ = number2;
}

double CalculatorMul::calc() const { return number1_ * number2_; }

void CalculatorDiv::setNumbers(double number1, double number2) {
  number1_ = number1;
  number2_ = number2;
  if (std::abs(number2_) < 0.001)
    number2_ = 0.001;
}

double CalculatorDiv::calc() const { return number1_ / number2_; }

void CalculatorHypot::setNumbers(double number1, double number2) {
  number1_ = number1;
  number2_ = number2;
}

double CalculatorHypot::calc() const { return std::hypot(number1_, number2_); }
} // namespace calculator_plugins

#include <pluginlib/class_list_macros.h>

PLUGINLIB_EXPORT_CLASS(calculator_plugins::CalculatorAdd,
                       calculator_base::CalculatorBase);
PLUGINLIB_EXPORT_CLASS(calculator_plugins::CalculatorSub,
                       calculator_base::CalculatorBase);
PLUGINLIB_EXPORT_CLASS(calculator_plugins::CalculatorMul,
                       calculator_base::CalculatorBase);
PLUGINLIB_EXPORT_CLASS(calculator_plugins::CalculatorDiv,
                       calculator_base::CalculatorBase);
PLUGINLIB_EXPORT_CLASS(calculator_plugins::CalculatorHypot,
                       calculator_base::CalculatorBase);
