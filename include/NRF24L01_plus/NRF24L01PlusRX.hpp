#pragma once
#include "NRF24L01Plus.hpp"

class NRF24L01PlusRX : public NRF24L01Plus {
public:
    NRF24L01PlusRX();
    void receiveMessage(uint8_t received_data[]);
};