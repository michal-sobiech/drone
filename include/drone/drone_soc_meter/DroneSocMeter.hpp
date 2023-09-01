#pragma once
#include "FourChannelMux.hpp"
#include "CellSocMeter.hpp"

#define DRONE_BAT_CELL_MIN_V 3400
#define DRONE_BAT_CELL_MAX_V 4200

class DroneSocMeter {
public:
    DroneSocMeter();

    // Fills the array with the percentages
    void get_cells_soc(unsigned int cells_soc[]);
private:
    FourChannelMux mux_;

    CellSocMeter cell_soc_meter_;

    // Fills the array with the voltages in mV
    void get_cells_voltage(unsigned int voltages[]);

    // Set the multiplexer to given cell and read its voltage in mV.
    // Uses a voltage divider.
    // cell_no is 0, 1, 2 or 3
    unsigned int get_single_cell_voltage(unsigned int cell_no);

    unsigned int get_single_cell_soc(unsigned int cell_no);
};