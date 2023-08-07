#pragma once
#include "NRF24L01Plus.hpp"

class NRF24L01PlusTX : public NRF24L01Plus {
public:
    NRF24L01PlusTX();
    void sendMessage(uint8_t data[]);
};