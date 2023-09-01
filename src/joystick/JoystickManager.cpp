#include "JoystickManager.hpp"
#include "pin_map.hpp"

JoystickManager::JoystickManager() {
    mux_ = FourChannelMux({
        JOYSTICK_MUX_SEL_H_GPIO_NO,
        JOYSTICK_MUX_SEL_L_GPIO_NO
    });

    adc_unit_ = AdcUnit(JOYSTICK_GPIO_NO, JOYSTICK_ADC_NO);
}

void JoystickManager::read_joystick_input(unsigned int joystick_data[4]) {
    for (unsigned int i = 0; i < 4; i++) {
        mux_.choose_channel(i);
        joystick_data[i] = adc_unit_.read_percentage();
    }
}