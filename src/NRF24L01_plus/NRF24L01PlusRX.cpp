#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "NRF24L01PlusRX.hpp"


NRF24L01PlusRX::NRF24L01PlusRX(spi_inst_t* spi, uint csn, uint ce):
NRF24L01Plus(spi, csn, ce)
{
    // RX module, so set the bit nr 0 (LSB) to 1
    uint8_t reg_contents = read_register(0xff);
    reg_contents = reg_contents | 0b00000001;
    write_register(0xff, reg_contents);
}