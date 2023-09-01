#pragma once
#include "NRF24L01.hpp"

class NRF24L01RX : public NRF24L01 {
public:
    NRF24L01RX();
    void receiveMessage(uint8_t received_data[]);
};