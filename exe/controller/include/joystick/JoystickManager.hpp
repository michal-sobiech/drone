#pragma once

#include <array>
#include <vector>
#include <utility>

#include "AdcUnit.hpp"
#include "FourChannelMux.hpp"
#include "Joystick.hpp"
#include "JoystickConfig.hpp"
#include "JoystickReadings.hpp"
#include "MuxConfig.hpp"


class JoystickManager {
public:
    JoystickManager(JoystickConfig& joystick_config, MuxConfig& mux_config);
    std::pair<JoystickReadings, JoystickReadings> read();
private:
    std::pair<Joystick, Joystick> joysticks_;
    FourChannelMux mux_;
    AdcUnit adc_unit_;
};