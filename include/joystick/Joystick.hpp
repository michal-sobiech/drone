#pragma once
#include <utility>
#include "hardware/adc.h"
#include "AdcGpio.hpp"

class Joystick {
public:
    Joystick();
    Joystick(AdcGpio x_axis_gpio, AdcGpio y_axis_gpio);
    std::pair<unsigned int, unsigned int> get_joystick_position();
private:
    AdcGpio x_axis_adc_gpio_;
    AdcGpio y_axis_adc_gpio_;
};