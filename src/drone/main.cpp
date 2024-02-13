#include "Drone.hpp"
#include "hardware/adc.h"
#include "pico/stdlib.h"
#include <iostream>

#define SYS_CLOCK_KHZ 80000

int main()
{
    const uint DRONE_SOC_METER_GPIO_NO = 26;
    const uint DRONE_SOC_METER_ADC_NO = 0;
    const uint DRONE_SOC_METER_MUX_SEL_H_GPIO_NO = 21;
    const uint DRONE_SOC_METER_MUX_SEL_L_GPIO_NO = 20;

    const uint FRONT_RIGHT_ENG_NO = 0;
    const uint FRONT_LEFT_ENG_NO = 1;
    const uint BACK_LEFT_ENG_NO = 2;
    const uint BACK_RIGHT_ENG_NO = 3;

    const uint ENG_PIO_NO = 0;

    const uint FRONT_RIGHT_ENG_PIN = 0;
    const uint FRONT_LEFT_ENG_PIN = 15;
    const uint BACK_LEFT_ENG_PIN = 16;
    const uint BACK_RIGHT_ENG_PIN = 28;

    const uint FRONT_RIGHT_ENG_SM = 0;
    const uint FRONT_LEFT_ENG_SM = 1;
    const uint BACK_LEFT_ENG_SM = 2;
    const uint BACK_RIGHT_ENG_SM = 3;

    stdio_init_all();
    adc_init();

    // Change the clock so that dshot600 works
    set_sys_clock_khz(SYS_CLOCK_KHZ, true);

    Drone drone = Drone();

    uint8_t received_data[PAYLOAD_LEN];
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    uint16_t rot_data[3];

    while(true) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(250);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(250);

        // drone.get_transceiver().receiveMessage(received_data);
        // // printf("Received data: %d\r\n", received_data[0]);
        // std::cout << "Received data: ";
        // for (uint i = 0; i < PAYLOAD_LEN; i++) {
        //     std::cout << unsigned(received_data[i]);
        //     if (i == PAYLOAD_LEN - 1) {
        //         std::cout << std::endl;
        //     } else {
        //         std::cout << ", ";
        //     }
        // }

        drone.get_mpu().get_3_axis_rotation(rot_data);
        printf("X: %d, Y: %d, Z: %d\r\n", unsigned(rot_data[0]), unsigned(rot_data[1]), unsigned(rot_data[2]));
    }
}