#pragma once
#include "AdcUnit.hpp"
#include "CellSocMeter.hpp"

#define CONTROLLER_BAT_MIN_V 2000
#define CONTROLLER_BAT_MAX_V 3000

class ControllerSocMeter {
public:
    ControllerSocMeter();

    // Number of percent
    unsigned int get_soc();
private:
    CellSocMeter cell_soc_meter_;
};