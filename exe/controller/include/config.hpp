#pragma once

#include <map>

#include "types.hpp"


enum PinFunction {
    RADIO_CE,
    RADIO_CSN,
    RADIO_SCK,
    RADIO_MOSI,
    RADIO_MISO,
    RADIO_IRQ
};


std::map<PinFunction, GpioNo> gpio_pins{
    {PinFunction::RADIO_CE, 0},
    {PinFunction::RADIO_CSN, 0},
    {PinFunction::RADIO_SCK, 0},
    {PinFunction::RADIO_MOSI, 0},
    {PinFunction::RADIO_MISO, 0},
    {PinFunction::RADIO_IRQ, 0}
};




