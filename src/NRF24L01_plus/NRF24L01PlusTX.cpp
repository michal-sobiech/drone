#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "NRF24L01PlusTX.hpp"

NRF24L01PlusTX::NRF24L01PlusTX() {}

NRF24L01PlusTX::NRF24L01PlusTX(spi_inst_t* spi, uint csn, uint ce):
NRF24L01Plus(spi, csn, ce)
{
    // TX module, so set the bit nr 0 (LSB) to 0
    uint8_t reg_contents = read_register(0xff);
    reg_contents = reg_contents & 0b11111110;
    write_register(0xff, reg_contents);
}

