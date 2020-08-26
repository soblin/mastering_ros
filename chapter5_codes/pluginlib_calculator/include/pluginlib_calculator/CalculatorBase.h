#ifndef PLUGINLIB_CALCULATOR_H_
#define PLUGINLIB_CALCULATOR_H_

namespace calculator_base {

class CalculatorBase {
public:
  CalculatorBase() {}
  virtual void setNumbers(double number1, double number2) = 0;
  virtual double calc() const = 0;
  virtual ~CalculatorBase() {}
};

} // namespace calculator_base
#endif /* PLUGINLIB_CALCULATOR_H_ */
