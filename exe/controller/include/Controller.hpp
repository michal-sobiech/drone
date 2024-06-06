#pragma once

#include <utility>

#include "ControllerSocMeter.hpp"
#include "ControllerSocMeterConfig.hpp"
#include "JoystickManager.hpp"
#include "JoystickManagerConfig.hpp"
#include "NRF24L01TX.hpp"
#include "Nrf24l01Config.hpp"


class Controller {
public:
    Controller(
        const Nrf24l01Config& nrf_config,
        const JoystickManagerConfig& joystick_manager_config,
        const ControllerSocMeterConfig& soc_meter_config
    );
    void main_loop();
    NRF24L01TX& get_radio();
    JoystickManager& get_joystick_manager();
    ControllerSocMeter& get_soc_meter();
private:
    NRF24L01TX radio_;
    JoystickManager joystick_manager_;
    ControllerSocMeter soc_meter_;
};