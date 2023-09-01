#include "AdcGpio.hpp"
#include "hardware/adc.h"

AdcUnit::AdcUnit() {}

AdcUnit::AdcUnit(unsigned int gpio_no, unsigned int adc_no):
    gpio_no_(gpio_no), adc_no_(adc_no) {}

unsigned int AdcUnit::get_adc_no() {
    return adc_no_;
};

unsigned int AdcUnit::get_gpio_no() {
    return gpio_no_;
}

unsigned int AdcUnit::read() {
    adc_gpio_init(gpio_no_);
    adc_select_input(adc_no_);
    return adc_read();
}

unsigned int AdcUnit::read_percent() {
    return (unsigned)(100.0 * float(read()) / 4096.0);
}