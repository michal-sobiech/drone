#include "hardware/adc.h"
#include "Controller.hpp"

Controller::Controller() {}

std::pair<unsigned int, unsigned int> Controller::getJoystickPosition() {\
    // Read X
    adc_gpio_init(ADC0_GPIO);
    adc_select_input(0);
    unsigned int x_value = adc_read();
    // Read Y
    adc_gpio_init(ADC1_GPIO);
    adc_select_input(1);
    unsigned int y_value = adc_read();

    return std:: make_pair(x_value, y_value);
}

NRF24L01Plus& Controller::getTransceiver() {
    return transceiver_;
};