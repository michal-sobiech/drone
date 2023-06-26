#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "NRF24L01Plus.hpp"


class NRF24L01PlusTX : NRF24L01Plus
{
public:
    NRF24L01PlusTX();
    NRF24L01PlusTX(spi_inst_t* spi, uint csn, uint ce);
};