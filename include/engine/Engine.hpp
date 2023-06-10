#include <cstdint>
#include <stdio.h>
#include <stdbool.h>

#include <pico/stdlib.h>
#include <hardware/pio.h>


class Engine
{
    public:
        Engine();
        Engine(PIO pio, uint state_machine_id, uint pin);
        void set_thrust(float thrust_level);
    private:
        PIO pio;
        uint state_machine_id;
        uint pin;
        uint percentage_to_DSHOT600(float thrust_level, char telemetry_bit);
};