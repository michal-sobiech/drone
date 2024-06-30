#include "hardware/adc.h"
#include "AdcUnit.hpp"


AdcUnit::AdcUnit() {}

AdcUnit::AdcUnit(unsigned int gpio_no, unsigned int adc_no):
    _gpio_no(gpio_no), _adc_no(adc_no) {}

unsigned int AdcUnit::get_adc_no() {
    return _adc_no;
};

unsigned int AdcUnit::get_gpio_no() {
    return _gpio_no;
}

unsigned int AdcUnit::read() {
    adc_gpio_init(_gpio_no);
    adc_select_input(_adc_no);
    return adc_read();
}

unsigned int AdcUnit::read_percentage() {
    return (unsigned)(100.0 * float(read()) / 4096.0);
}