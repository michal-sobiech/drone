#include "Engine.hpp"

#include "hardware/pio.h"
#include "dshot.pio.h"

#include "types.hpp"


#define DSHOT600_STEPS 2048


Engine::Engine(PIO pio, uint state_machine_no, uint pin):
    pio_(pio),
    state_machine_no_(state_machine_no),
    pin_(pin)
{
    uint offset = pio_add_program(pio_, &dshot_program);
    dshot_program_init(pio_, state_machine_no_, offset, pin_);
}


void Engine::set_thrust(float thrust_percent) 
{
    DshotCommand command = percentage_to_DSHOT600(thrust_percent, false);
    send_esc_command(command);
}


DshotCommand Engine::percentage_to_DSHOT600(float thrust_percent, bool telemetry)
{
    uint16_t telemetry_bit = static_cast<uint16_t> telemetry;
    uint16_t throttle_value = (uint)(thrust_percent * DSHOT600_STEPS);
    uint value = throttle_value << 1 + telemetry_bit;
    uint crc_checksum = (value ^ (value >> 4) ^ (value >> 8)) & 0x0F;
    uint dshot600_command = (value << 4) + crc_checksum;
    return dshot600_command;
}


void Engine::send_esc_command(DshotCommand command) {
    pio_sm_put(pio_, state_machine_no_, command);
}