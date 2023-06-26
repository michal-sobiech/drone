#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "NRF24L01Plus.hpp"


class NRF24L01PlusRX : NRF24L01Plus
{
public:
    NRF24L01PlusRX();
    NRF24L01PlusRX(spi_inst_t* spi, uint csn, uint ce);
};