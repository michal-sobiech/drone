#include "Controller.hpp"
#include "NRF24L01PlusTX.hpp"
#include "Joystick.hpp"
#include "AdcGpio.hpp"
#include "ControllerSocMeter.hpp"

Controller::Controller() {
    transceiver_ = NRF24L01PlusTX();
    joystick_ = Joystick(AdcGpio(26, 0), AdcGpio(27, 1));
    soc_meter_ = ControllerSocMeter();
}

NRF24L01PlusTX& Controller::get_transceiver() {
    return transceiver_;
};

ControllerSocMeter& Controller::get_soc_meter() {
    return soc_meter_;
}

std::pair<unsigned int, unsigned int> Controller::get_joystick_position() {
    return joystick_.get_joystick_position();
}