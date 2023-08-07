#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "Drone.hpp"

#define SYS_CLOCK_KHZ 80000

int main()
{
    stdio_init_all();
    adc_init();

    // Change the clock so that dshot600 works
    set_sys_clock_khz(SYS_CLOCK_KHZ, true);

    Drone drone = Drone();

    uint8_t received_data[5];
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    while(true) {
        drone.get_transceiver().receiveMessage(received_data);
        printf("Received data: %d\r\n", received_data[0]);

        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(50);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(50);
    }
}