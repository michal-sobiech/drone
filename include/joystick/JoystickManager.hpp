#pragma once
#include "FourChannelMux.hpp"
#include "AdcUnit.hpp"

class JoystickManager {
public:
    JoystickManager();
    void read_joystick_input(unsigned int joystick_one_data[4]);
private:
    FourChannelMux mux_;
    AdcUnit adc_unit_;
};