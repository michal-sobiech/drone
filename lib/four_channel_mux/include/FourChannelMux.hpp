#pragma once


class FourChannelMux {
public:
    FourChannelMux();
    FourChannelMux(unsigned int sel_pin_h, unsigned int sel_pin_l);
    void choose_channel(unsigned int cell_no);
private:
    unsigned int _sel_pin_h;
    unsigned int _sel_pin_l;
};