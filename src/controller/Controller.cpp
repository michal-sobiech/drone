#include "Controller.hpp"
#include <utility>
#include "NRF24L01TX.hpp"
#include "JoystickManager.hpp"
#include "AdcUnit.hpp"
#include "ControllerSocMeter.hpp"

Controller::Controller() {
    transceiver_ = NRF24L01TX();
    // joystick_ = Joystick(AdcUnit(26, 0), AdcUnit(27, 1));
    soc_meter_ = ControllerSocMeter();
}

NRF24L01TX& Controller::get_transceiver() {
    return transceiver_;
};

ControllerSocMeter& Controller::get_soc_meter() {
    return soc_meter_;
}

JoystickManager& Controller::get_joystick_manager() {
    return joystick_manager_;
};

std::pair<std::pair<int, int>, std::pair<int, int>>
        Controller::get_joystick_positions() {
    unsigned int joystick_data[4];
    joystick_manager_.read_joystick_input(joystick_data);

    // Parse the data into a more readable form
    std::pair<int, int> first_joystick_data = std::make_pair(
        joystick_data[0], joystick_data[1]);
    std::pair<int, int> second_joystick_data = std::make_pair(
        joystick_data[2], joystick_data[3]);

    return std::pair<std::pair<int, int>, std::pair<int, int>>(
        first_joystick_data, second_joystick_data
    );
}