#pragma once
#include "AdcUnit.hpp"

class CellSocMeter {
public:
    CellSocMeter();
    CellSocMeter(unsigned int min_voltage,
                 unsigned int max_voltage,
                 AdcUnit adc_unit);

    // Returns number of percents
    unsigned int get_soc();
private:
    // In mV
    unsigned int min_voltage_;
    unsigned int max_voltage_;
    unsigned int get_voltage();

    AdcUnit adc_unit_;
};