#pragma once
#include "NRF24L01.hpp"

class NRF24L01TX : public NRF24L01 {
public:
    NRF24L01TX();
    void sendMessage(uint8_t data[]);
};