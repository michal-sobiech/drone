#include "CellSocMeter.hpp"
#include "AdcUnit.hpp"

CellSocMeter::CellSocMeter(unsigned int min_voltage,
    unsigned int max_voltage, AdcUnit adc_gpio): min_voltage_(min_voltage), 
    max_voltage_(max_voltage), adc_gpio_(AdcUnit(adc_gpio)) {}

unsigned int CellSocMeter::get_voltage() {
    float percent = float(adc_.read()) / 4096.0;
    unsigned int half_voltage = (unsigned)(percent * max_battery_voltage_);
    return half_voltage * 2;
}

unsigned int CellSocMeter::get_soc() {
    unsigned int battery_voltage = get_voltage_level();
    unsigned int rel_bat_voltage = battery_voltage - min_battery_voltage_;
    unsigned int min_max_gap = max_battery_voltage_ - min_battery_voltage_;
    return (unsigned)(100 * rel_bat_voltage / min_max_gap); 
}