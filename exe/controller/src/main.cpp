#include <utility>
#include <iostream>

#include "pico/stdlib.h"
#include "hardware/adc.h"

#include "Controller.hpp"

#include "ControllerSocMeterConfig.hpp"
#include "JoystickManagerConfig.hpp"
#include "Nrf24l01Config.hpp"
#include "config.hpp"


int main() {
    stdio_init_all();
    adc_init();

    Nrf24l01Config radio_config = Nrf24l01Config(
        
    );
    JoystickManagerConfig joystick_man_config = JoystickManagerConfig();
    ControllerSocMeterConfig soc_meter_config = ControllerSocMeterConfig();

    Controller controller = Controller(
        radio_config, joystick_man_config, soc_meter_config
    );
    controller.main_loop();

    return 0;
}