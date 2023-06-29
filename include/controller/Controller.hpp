#pragma once
#include "NRF24L01Plus.hpp"
#include "Joystick.hpp"

class Controller {
public:
    Controller();
    NRF24L01Plus& get_transceiver();
    Joystick& get_joystick();
    std::pair<unsigned int, unsigned int> get_joystick_position(); 
private:
    NRF24L01Plus transceiver_;
    Joystick joystick_;
};