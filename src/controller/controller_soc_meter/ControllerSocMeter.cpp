#include "ControllerSocMeter.hpp"
#include <iostream>
#include "AdcGpio.hpp"
#include "CellSocMeter.hpp"

ControllerSocMeter::ControllerSocMeter() {
    cell_soc_meter_ = CellSocMeter(
        CONTROLLER_SOC_METER_MIN_V,
        CONTROLLER_SOC_METER_MAX_V, 
        AdcGpio(0, 26)
    );
}

unsigned int ControllerSocMeter::get_soc() {
    return cell_soc_meter_.get_soc();
}

