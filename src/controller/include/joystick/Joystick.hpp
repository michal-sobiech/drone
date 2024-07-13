#include "JoystickConfig.hpp"

#include "JoystickReadings.hpp"


class Joystick {
private:
    Joystick(
        uint8_t vrx_gpio_no,
        uint8_t vry_gpio_no,
        uint8_t sw_gpio_no
    );
public:
    JoystickReadings read();
};