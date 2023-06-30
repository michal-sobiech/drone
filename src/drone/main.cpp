#include "Drone.hpp"

#define SYS_CLOCK_KHZ 80000


int main()
{
    // Change the clock so that dshot600 works
    set_sys_clock_khz(SYS_CLOCK_KHZ, true);

    stdio_init_all();

    Drone drone = Drone();
}