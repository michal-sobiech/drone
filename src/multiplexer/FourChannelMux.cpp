#include "FourChannelMux.hpp"
#include <cstring>

FourChannelMux::FourChannelMux(unsigned int selection_pins[2]) {
    std::memcpy(selection_pins_, selection_pins, sizeof(unsigned int) * 2);
}

void FourChannelMux::choose_channel(unsigned int cell_no) {
    bool h_bit = (cell_no & 0b10) >> 1;
    bool l_bit = cell_no & 0b01;

    gpio_put(selection_pins_[0], h_bit);
    gpio_put(selection_pins_[1], l_bit);
}