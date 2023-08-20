#include <utility>
#include <iostream>
#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "Controller.hpp"

int main() {
    stdio_init_all();
    adc_init();

    Controller controller = Controller();
    std::pair<unsigned int, unsigned int> joystick_data;

    uint8_t sent_data[PAYLOAD_LEN];
    for (uint i = 0; i < PAYLOAD_LEN; i++) {
        sent_data[i] = i + 5;
    }

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true) {
        // joystick_data = controller.get_joystick_position();
        // printf("X axis: %d, Y axis: %d\r\n", joystick_data.first, joystick_data.second);

        // controller.get_transceiver().sendMessage(sent_data);
        // std::cout << "Sent data: ";
        // for (uint i = 0; i < PAYLOAD_LEN; i++) {
        //     std::cout << unsigned(sent_data[i]);
        //     if (i == PAYLOAD_LEN - 1) {
        //         std::cout << std::endl;
        //     } else {
        //         std::cout << ", ";
        //     }
        // }

        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(500);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(500);
    }
    return 0;
}