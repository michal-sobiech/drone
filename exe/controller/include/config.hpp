#pragma once

#include <map>

#include "types.hpp"


enum PinFunction {
    RADIO_CE = 0,
    RADIO_CSN = 0,
    RADIO_SCK = 0,
    RADIO_MOSI = 0,
    RADIO_MISO = 0,
    RADIO_IRQ = 0
};


std::map<PinFunction, GpioNo> gpio_pins{
    {PinFunction::RADIO_CE, 0},
    {PinFunction::RADIO_CSN, 0},
    {PinFunction::RADIO_SCK, 0},
    {PinFunction::RADIO_MOSI, 0},
    {PinFunction::RADIO_MISO, 0},
    {PinFunction::RADIO_IRQ, 0}
};

constexpr
auto are_keys_and_values_unique = [gpio_pins]() => {
    for (auto it1 = myMap.begin(); it1 != myMap.end(); ++it1) {
        for (auto it2 = it1; it2 != myMap.end(); ++it2) {
            if (*it1 == *it2) {
                return false;
            }
        }
    }
    return true;
}
static_assert(are_eys_and_values_unique(), "SAMPLE TEXT");