#include <utility>
#include "Joystick.hpp"
#include "AdcGpio.hpp"

Joystick::Joystick() {}

Joystick::Joystick(AdcGpio x_axis_adc_gpio, AdcGpio y_axis_adc_gpio) {
    x_axis_adc_gpio_ = x_axis_adc_gpio;
    y_axis_adc_gpio_ = x_axis_adc_gpio;
}

std::pair<unsigned int, unsigned int> Joystick::get_joystick_position() {
    // Read X
    adc_gpio_init(x_axis_adc_gpio_.get_adc_no());
    adc_select_input(x_axis_adc_gpio_.get_gpio_no());
    unsigned int x_value = adc_read();
    // Read Y
    adc_gpio_init(y_axis_adc_gpio_.get_adc_no());
    adc_select_input(y_axis_adc_gpio_.get_gpio_no());
    unsigned int y_value = adc_read();

    return std::make_pair(x_value, y_value);
}