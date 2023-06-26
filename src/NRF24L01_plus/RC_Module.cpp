#include "RC_Module.hpp"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <cstdio>

RC_Module::RC_Module() {}

RC_Module::RC_Module(spi_inst_t* spi, uint csn, uint ce):
spi_(spi), csn_(csn), ce_(ce)
{
    spi_init(spi_, SPI_BAUDRATE);

    gpio_set_function(SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO_PIN, GPIO_FUNC_SPI);

    // NRF24L01+ config
    // cnsHigh();
    // csnLow();
    sleep_ms(11);   // little over 10,3 ms

    // At 0x00:
    // bit 0 does not matter because it will be set later
    // bit 1 = 1 because we turn the module on,
    // bit 2 = 0 because we want the 1 byte crc
    // bit 3 = 1 because we want the crc
    // bits 4 - 7 = 0, but I dont really know why

    write_register(0x00, 0b00001010);
    sleep_us(1500);

}

void RC_Module::write_register(uint8_t reg, uint8_t data)
{
    uint8_t cmd = 0b00100000 | (reg & 0b00011111);
    // csnLow();

    // Choose the register
    spi_write_blocking(spi_, &cmd, 1);

    // Write the data
    spi_write_blocking(spi_, &data, 1);

    // csnHigh();
}

uint8_t RC_Module::read_register(uint8_t reg)
{
    uint8_t read_data;
    uint8_t cmd = 0b00011111 & reg;
    // csnLow();
    
    // Choose the register
    spi_write_blocking(spi_, &cmd, 1);

    // Read the data
    // The 0xff is sent, because it is recognized as
    // a NOP command by the NRF24L01+ module.
    spi_read_blocking(spi_, 0xff, &read_data, 1);

    // csnHigh();

    return read_data;
}