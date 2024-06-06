#pragma once

#include "AdcUnit.hpp"
#include "CellSocMeter.hpp"
#include "ControllerSocMeterConfig.hpp"


class ControllerSocMeter {
public:
    ControllerSocMeter(ControllerSocMeterConfig& config);
    float get_soc();
private:
    CellSocMeter cell_soc_meter_;
};