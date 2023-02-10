#include "dshot.pio.h"
#include "Engine.hpp"

#define DSHOT600_MAX_STEPS 2048


Engine::Engine() {}

Engine::Engine(PIO pio, uint state_machine_id, uint pin)
{
    this->pio = pio;
    this->state_machine_id = state_machine_id;
    this->pin = pin;

    // Initiate the pio program
    uint offset = pio_add_program(pio, &dshot_program);
    dshot_program_init(pio, state_machine_id, offset, pin);
}

void Engine::set_thrust(float thrust_level) 
{
    if ((thrust_level < 0) || (thrust_level > 1)) {
        // Values out of bounds
        return;
    }
    uint dshot600_code = percentage_to_DSHOT600(thrust_level, 0);
    pio_sm_put(pio, state_machine_id, dshot600_code);
}

uint Engine::percentage_to_DSHOT600(float thrust_level, char telemetry_bit)
{
    uint throttle_value = (uint)(thrust_level * DSHOT600_MAX_STEPS);
    uint value = throttle_value << 1 + telemetry_bit;
    uint crc_checksum = (value ^ (value >> 4) ^ (value >> 8)) & 0x0F;
    uint dshot600_code = (value << 4) + crc_checksum;
    return dshot600_code;
}