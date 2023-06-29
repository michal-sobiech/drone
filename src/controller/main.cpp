#include <utility>
#include "pico/stdlib.h"
#include "Controller.hpp"

int main() {
    stdio_init_all();
    adc_init();

    Controller controller = Controller();
    std::pair<unsigned int, unsigned int> data;

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true) {
        data = controller.getJoystickPosition();
        printf("X axis: %d, Y axis: %d\r\n", data.first, data.second);

        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(250);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(250);
    }
    return 0;
}