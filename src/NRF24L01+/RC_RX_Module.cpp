#include "RC_RX_Module.hpp"


RC_RX_Module::RC_RX_Module(spi_inst_t spi, uint csn, uint ce):
RC_Module(spi_inst_t spi, uint csn, uint ce)
{
    // RX module, so set the bit nr 0 (LSB) to 1
    uint8_t reg_contents = read_register(0xff);
    reg_contents = reg_contents | 0b0000_0001;
    write_register(0xff, reg_contents);
}