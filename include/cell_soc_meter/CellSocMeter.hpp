#pragma once
#include "AdcGpio.hpp"

class CellSocMeter {
public:
    CellSocMeter(unsigned int min_voltage,
                 unsigned int max_voltage);

    // Returns number of percents
    unsigned int get_soc();
private:
    // In mV
    unsigned int min_voltage_;
    unsigned int max_voltage_;
    unsigned int get_voltage();

    AdcGpio adc_gpio_;
};