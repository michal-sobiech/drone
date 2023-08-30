#include "AdcGpio.hpp"

AdcGpio::AdcGpio() {}

AdcGpio::AdcGpio(unsigned int adc_no, unsigned int gpio_no) {
    adc_no_ = adc_no;
    gpio_no = gpio_no;
}

unsigned int AdcGpio::get_adc_no() {
    return adc_no_;
};

unsigned int AdcGpio::get_gpio_no() {
    return gpio_no_;
}

uint AdcGpio::read() {
    adc_gpio_init(get_adc_no());
    adc_select_input(get_gpio_no());
    return adc_read();
}