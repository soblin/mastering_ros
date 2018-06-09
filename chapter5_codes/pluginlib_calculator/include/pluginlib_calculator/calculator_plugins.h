#ifndef PLUGINLIB_CALCULATOR_CALCULATOR_PLUGINS_H_
#define PLUGINLIB_CALCULATOR_CALCULATOR_PLUGINS_H_

#include <pluginlib_calculator/calculator_base.h>
#include <cmath>
#include <iostream>

namespace calculator_plugins{
class Add : public calculator_base::calc_functions
{
public:
    Add(){
        number1_ = 0;
        number2_ = 0;
    }

    void get_numbers(double number1, double number2){
        try{
            number1_ = number1;
            number2_ = number2;
        }
        catch(int e){
            std::cerr << "Exception while inputting numbers" << std::endl;
        }
            
    }

    double operation(){
        return (number1_ + number2_);
    }

private:
    double number1_;
    double number2_;
};
};
#endif
