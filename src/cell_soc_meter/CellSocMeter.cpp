#include "CellSocMeter.hpp"
#include "AdcUnit.hpp"

CellSocMeter::CellSocMeter() {}

CellSocMeter::CellSocMeter(unsigned int min_voltage,
    unsigned int max_voltage, AdcUnit adc_unit_): min_voltage_(min_voltage), 
    max_voltage_(max_voltage), adc_unit_(AdcUnit(adc_unit_)) {}

unsigned int CellSocMeter::get_voltage() {
    float percent = float(adc_unit_.read()) / 4096.0;
    unsigned int half_voltage = (unsigned)(percent * max_voltage_);
    return half_voltage * 2;
}

unsigned int CellSocMeter::get_soc() {
    unsigned int battery_voltage = get_voltage();
    unsigned int rel_bat_voltage = battery_voltage - min_voltage_;
    unsigned int min_max_gap = max_voltage_ - min_voltage_;
    return (unsigned)(100 * rel_bat_voltage / min_max_gap); 
}