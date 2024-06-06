#pragma once

#include "pico/stdlib.h"

#include "StaticCheckedArray.hpp"

#include "types.hpp"


struct EngineManagerConfig {
    PIO pio;
    StaticCheckedArray<GpioNo, 4> engine_pins;
};