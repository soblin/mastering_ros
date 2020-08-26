#ifndef CALCULATOR_PLUGINS_H_
#define CALCULATOR_PLUGINS_H_

#include <pluginlib_calculator/CalculatorBase.h>

namespace calculator_plugins
{
class CalculatorAdd : public calculator_base::CalculatorBase
{
public:
  CalculatorAdd(){};
  virtual void setNumbers(double number1, double number2) override;
  virtual double calc() const override;
  virtual ~CalculatorAdd()
  {
  }

private:
  double number1_ = 0;
  double number2_ = 0;
};

class CalculatorSub : public calculator_base::CalculatorBase
{
public:
  CalculatorSub(){};
  virtual void setNumbers(double number1, double number2) override;
  virtual double calc() const override;
  virtual ~CalculatorSub()
  {
  }

private:
  double number1_ = 0;
  double number2_ = 0;
};

class CalculatorMul : public calculator_base::CalculatorBase
{
public:
  CalculatorMul(){};
  virtual void setNumbers(double number1, double number2) override;
  virtual double calc() const override;
  virtual ~CalculatorMul()
  {
  }

private:
  double number1_ = 0;
  double number2_ = 0;
};

class CalculatorDiv : public calculator_base::CalculatorBase
{
public:
  CalculatorDiv()
  {
  }
  virtual void setNumbers(double number1, double number2) override;
  virtual double calc() const override;
  virtual ~CalculatorDiv()
  {
  }

private:
  double number1_ = 0;
  double number2_ = 0;
};

class CalculatorHypot : public calculator_base::CalculatorBase
{
public:
  CalculatorHypot(){};
  virtual void setNumbers(double number1, double number2) override;
  ;
  virtual double calc() const override;
  virtual ~CalculatorHypot()
  {
  }

private:
  double number1_ = 0;
  double number2_ = 0;
};

}  // namespace calculator_plugins
#endif /* CALCULATOR_PLUGINS_H_ */
