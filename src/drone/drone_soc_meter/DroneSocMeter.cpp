#include "DroneSocMeter.hpp"
#include "pin_map.hpp"
#include "FourChannelMux.hpp"
#include "CellSocMeter.hpp"

DroneSocMeter::DroneSocMeter() {
    mux_ = FourChannelMux(
        DRONE_SOC_METER_MUX_SEL_H_GPIO_NO,
        DRONE_SOC_METER_MUX_SEL_L_GPIO_NO
    );

    cell_soc_meter_ = CellSocMeter(
        DRONE_BAT_CELL_MIN_V,
        DRONE_BAT_CELL_MAX_V,
        AdcUnit(DRONE_SOC_METER_ADC_NO, DRONE_SOC_METER_GPIO_NO)
    );
}

void DroneSocMeter::get_cells_soc(unsigned int cells_soc[]) {
    for (unsigned int i = 0; i < 4; i++) {
        cells_soc[i] = get_single_cell_soc(i);
    }
}

unsigned int DroneSocMeter::get_single_cell_soc(unsigned int cell_no) {
    mux_.choose_channel(cell_no);
    return cell_soc_meter_.get_soc();
}