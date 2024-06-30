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
    _radio = NRF24L01TX(nrf_config);
    _joystick_manager = JoystickManager(joystick_manager_config);
    _soc_meter = ControllerSocMeter(soc_meter_config);
}

void main_loop() {}

NRF24L01TX& Controller::get_radio() {
    return _radio;
}

JoystickManager& Controller::get_joystick_manager() {
    return _joystick_manager;
}

ControllerSocMeter& Controller::get_soc_meter() {
    return _soc_meter;
}
