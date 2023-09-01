#pragma once

class FourChannelMux {
public:
    FourChannelMux(unsigned int selection_pins_[2]);
    void choose_channel(unsigned int cell_no);
private:
    // First one is H, second is L
    unsigned int selection_pins_[2];
};