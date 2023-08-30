#include <utility>
#include "hardware/adc.h"
#include "Joystick.hpp"
#include "AdcGpio.hpp"

Joystick::Joystick() {}

Joystick::Joystick(AdcGpio x_axis_adc_gpio, AdcGpio y_axis_adc_gpio) {
    x_axis_adc_gpio_ = x_axis_adc_gpio;
    y_axis_adc_gpio_ = x_axis_adc_gpio;
}

std::pair<unsigned int, unsigned int> Joystick::get_joystick_position() {
    // Read X
    unsigned int x_value = x_axis_adc_gpio_.read();
    // Read Y
    unsigned int y_value = y_axis_adc_gpio_.read();

    return std::make_pair(x_value, y_value);
}