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

    int received_data;
    while(true) {
        received_data = drone.get_transceiver().receiveByte();
        printf("Received data: %d", received_data);

        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(150);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(150);
    }
}