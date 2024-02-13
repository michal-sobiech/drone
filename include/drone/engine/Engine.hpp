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
        void set_thrust(float thrust_percent);
    private:
        PIO pio_;
        uint state_machine_id_;
        uint pin_;
        void engine_setup();
        uint percentage_to_DSHOT600(float thrust_percent, char telemetry_bit);
};