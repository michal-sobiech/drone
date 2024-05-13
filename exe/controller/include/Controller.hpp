#pragma once
#include <utility>
#include "NRF24L01TX.hpp"
#include "JoystickManager.hpp"
#include "ControllerSocMeter.hpp"

class Controller {
public:
    Controller();
    NRF24L01TX& get_transceiver();
    JoystickManager& get_joystick_manager();
    ControllerSocMeter& get_soc_meter();

    // Returns pairs of numbers of percent
    std::pair<std::pair<int, int>, std::pair<int, int>> get_joystick_positions();
private:
    NRF24L01TX transceiver_;
    JoystickManager joystick_manager_;
    ControllerSocMeter soc_meter_;
};