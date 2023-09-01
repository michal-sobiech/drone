#pragma once
#include <utility>
#include "AdcUnit.hpp"

class Joystick {
public:
    Joystick();
    Joystick(AdcUnit x_axis_gpio, AdcUnit y_axis_gpio);
    std::pair<unsigned int, unsigned int> get_joystick_position();
private:
    AdcUnit x_axis_adc_gpio_;
    AdcUnit y_axis_adc_gpio_;
};