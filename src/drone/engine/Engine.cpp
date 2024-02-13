#include <hardware/pio.h>
#include "dshot.pio.h"
#include "Engine.hpp"

#define DSHOT600_MAX_STEPS 2048


Engine::Engine() {}

Engine::Engine(PIO pio, uint state_machine_id, uint pin):
pio_(pio), state_machine_id_(state_machine_id), pin_(pin)
{
    // Initiate the pio program
    uint offset = pio_add_program(pio_, &dshot_program);
    dshot_program_init(pio_, state_machine_id_, offset, pin_);
}

void Engine::set_thrust(float thrust_percent) 
{
    if ((thrust_percent < 0) || (thrust_percent > 1)) {
        // Values out of bounds
        return;
    }
    uint dshot600_code = percentage_to_DSHOT600(thrust_percent, 0);
    pio_sm_put(pio_, state_machine_id_, dshot600_code);
}

uint Engine::percentage_to_DSHOT600(float thrust_percent, char telemetry_bit)
{
    uint throttle_value = (uint)(thrust_percent * DSHOT600_MAX_STEPS);
    uint value = throttle_value << 1 + telemetry_bit;
    uint crc_checksum = (value ^ (value >> 4) ^ (value >> 8)) & 0x0F;
    uint dshot600_code = (value << 4) + crc_checksum;
    return dshot600_code;
}