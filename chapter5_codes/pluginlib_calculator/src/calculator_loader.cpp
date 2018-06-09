#include <boost/shared_ptr.hpp>
#include <pluginlib/class_loader.h>
#include <pluginlib_calculator/calculator_base.h>

int main(int argc, char **argv){
    //ros::init(argc, argv, "calculator_loader")
    pluginlib::ClassLoader<calculator_base::calc_functions> calc_loader("pluginlib_calculator", "calculator_base::calc_functions");
    try{
        boost::shared_ptr<calculator_base::calc_functions> add = calc_loader.createInstance("pluginlib_calculator/Add");
        add->get_numbers(10.0, 10.0);
        double result = add->operation();
        ROS_INFO("Triangle area : %.2f", result);
    }
    catch(pluginlib::PluginlibException& e){
        ROS_ERROR("The plugin failed to load for some reason. Error : %s", e.what());
    }

    return 0;
}
