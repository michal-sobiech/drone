#pragma once

#include <map>

#include "types.hpp"


enum class PinFunction {
    NRF24L01_CE,
    NRF24L01_CSN,
    NRF24L01_SCK,
    NRF24L01_MOSI,
    NRF24L01_MISO,
    NRF24L01_IRQ,

    
};


const std::map<const PinFunction, const GpioNo> gpio_pins{
    {PinFunction::NRF24L01_CE, 0},
    {PinFunction::NRF24L01_CSN, 5},
    {PinFunction::NRF24L01_SCK, 2},
    {PinFunction::NRF24L01_MOSI, 3},
    {PinFunction::NRF24L01_MISO, 4},
    {PinFunction::NRF24L01_IRQ, 1},


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