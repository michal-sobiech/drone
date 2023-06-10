#include "RC_TX_Module.hpp"


RC_TX_Module::RC_TX_Module() {}

RC_TX_Module(spi_inst_t spi, uint csn, uint ce):RC_Module(spi_inst_t spi, uint csn, uint ce)
{
    // TX module, so set the bit nr 0 (LSB) to 0
    uint8_t reg_contents = read_register(0xff);
    reg_contents = reg_contents & 0b1111_1110;
    write_register(0xff, reg_contents);
}

