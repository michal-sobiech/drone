#include "FourChannelMux.hpp"
#include <cstring>
#include "pico/stdlib.h"

FourChannelMux::FourChannelMux() {}

FourChannelMux::FourChannelMux(unsigned int sel_pin_h, unsigned int sel_pin_l):
    sel_pin_h_(sel_pin_h), sel_pin_l_(sel_pin_l) {}

void FourChannelMux::choose_channel(unsigned int cell_no) {
    bool h_bit = (cell_no & 0b10) >> 1;
    bool l_bit = cell_no & 0b01;

    gpio_put(sel_pin_h_, h_bit);
    gpio_put(sel_pin_l_, l_bit);
}