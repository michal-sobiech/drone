#include "Drone.hpp"
#include "hardware/adc.h"
#include "pico/stdlib.h"
#include <iostream>

#define SYS_CLOCK_KHZ 80000

int main()
{
    mcu_setup();
    Drone drone = Drone();
    drone.
}

void mcu_setup() {
    stdio_init_all();
    adc_init();
    // Change the clock so that dshot600 works
    set_sys_clock_khz(SYS_CLOCK_KHZ, true);
}