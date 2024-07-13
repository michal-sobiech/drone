#pragma once

#include <vector>

#include "CellSocMeter.hpp"
#include "FourChannelMux.hpp"


class DroneSocMeter {
public:
    DroneSocMeter(
        float min_voltage,
        float max_voltage
    );

    std::vector<float> read();

    FourChannelMux& get_mux();
    CellSocMeter& get_soc_meter();
private:
    FourChannelMux mux_;
    CellSocMeter _soc_meter;
};