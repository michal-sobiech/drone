#include "Controller.hpp"
#include "NRF24L01TX.hpp"
#include "Joystick.hpp"
#include "AdcUnit.hpp"
#include "ControllerSocMeter.hpp"

Controller::Controller() {
    transceiver_ = NRF24L01TX();
    joystick_ = Joystick(AdcUnit(26, 0), AdcUnit(27, 1));
    soc_meter_ = ControllerSocMeter();
}

NRF24L01TX& Controller::get_transceiver() {
    return transceiver_;
};

ControllerSocMeter& Controller::get_soc_meter() {
    return soc_meter_;
}

std::pair<unsigned int, unsigned int> Controller::get_joystick_position() {
    return joystick_.get_joystick_position();
}