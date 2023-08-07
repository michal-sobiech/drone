#include "Controller.hpp"
#include "NRF24L01PlusTX.hpp"
#include "Joystick.hpp"
#include "AdcGpio.hpp"

Controller::Controller() {
    transceiver_ = NRF24L01PlusTX();
    joystick_ = Joystick(AdcGpio(26, 0), AdcGpio(27, 1));
}

NRF24L01PlusTX& Controller::get_transceiver() {
    return transceiver_;
};

std::pair<unsigned int, unsigned int> Controller::get_joystick_position() {
    return joystick_.get_joystick_position();
}