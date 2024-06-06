#include "Controller.hpp"

#include <cstdint>
#include <utility>

#include "AdcUnit.hpp"
#include "ControllerSocMeter.hpp"
#include "JoystickManager.hpp"
#include "NRF24L01TX.hpp"
#include "JoystickManagerConfig.hpp"


Controller::Controller(
    const Nrf24l01Config& nrf_config,
    const JoystickManagerConfig& joystick_manager_config,
    const ControllerSocMeterConfig& soc_meter_config
) {
    radio_ = NRF24L01TX(nrf_config);
    joystick_manager_ = JoystickManager(joystick_manager_config);
    soc_meter_ = ControllerSocMeter(soc_meter_config);
}

void main_loop() {}

NRF24L01TX& Controller::get_radio() {
    return radio_;
}

JoystickManager& Controller::get_joystick_manager() {
    return joystick_manager_;
}

ControllerSocMeter& Controller::get_soc_meter() {
    return soc_meter_;
}
