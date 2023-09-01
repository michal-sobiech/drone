#include "ControllerSocMeter.hpp"
#include <iostream>
#include "pin_map.hpp"
#include "AdcUnit.hpp"
#include "CellSocMeter.hpp"

ControllerSocMeter::ControllerSocMeter() {
    cell_soc_meter_ = CellSocMeter(
        CONTROLLER_BAT_MIN_V,
        CONTROLLER_BAT_MAX_V, 
        AdcUnit(CONTROLLER_SOC_METER_ADC_NO, CONTROLLER_SOC_METER_GPIO_NO)
    );
}

unsigned int ControllerSocMeter::get_soc() {
    return cell_soc_meter_.get_soc();
}