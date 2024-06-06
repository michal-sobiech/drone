#pragma once

#include <cstdint>
#include <cstdio>
#include <cstdbool>

#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "types.hpp"

using DshotCommand = uint16_t;


class Engine {
public:
    Engine(PIO pio, uint8_t state_machine_no, GpioNo pin);
    void set_thrust(float thrust);
private:
    PIO pio_;
    StateMachineNo state_machine_no_;
    GpioNo pin_;

    DshotCommand percentage_to_DSHOT600(
        float thrust_percent,
        bool telemetry_bit
    );
    void send_dshot_cmd_to_esc(DshotCommand command);
};