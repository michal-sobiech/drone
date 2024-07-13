#pragma once


class AdcUnit {
public:
    AdcUnit();
    AdcUnit(unsigned int adc_no, unsigned int gpio_no);
    unsigned int get_adc_no();
    unsigned int get_gpio_no();

    // Recorded ADC voltage divided by max ADC voltage.
    // Returns number of percent
    unsigned int read_percentage();

    // Raw ADC value, from 0 to 4096
    unsigned int read();
private:
    unsigned int _adc_no;
    unsigned int _gpio_no;
};