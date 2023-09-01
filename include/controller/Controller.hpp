#pragma once
#include "NRF24L01TX.hpp"
#include "Joystick.hpp"
#include "ControllerSocMeter.hpp"

class Controller {
public:
    Controller();
    NRF24L01TX& get_transceiver();
    Joystick& get_joystick();
    ControllerSocMeter& get_soc_meter();
    std::pair<unsigned int, unsigned int> get_joystick_position(); 
private:
    NRF24L01TX transceiver_;
    Joystick joystick_;
    ControllerSocMeter soc_meter_;
};