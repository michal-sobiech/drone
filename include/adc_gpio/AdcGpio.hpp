#pragma once

class AdcGpio {
public:
    AdcGpio();
    AdcGpio(unsigned int adc_no, unsigned int gpio_no);
    unsigned int get_adc_no();
    unsigned int get_gpio_no();
    unsigned int read();
private:
    unsigned int adc_no_;
    unsigned int gpio_no_;
};