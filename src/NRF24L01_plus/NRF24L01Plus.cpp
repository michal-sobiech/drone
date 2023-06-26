#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <cstdio>
#include "NRF24L01Plus.hpp"

NRF24L01Plus::NRF24L01Plus() {}

NRF24L01Plus::NRF24L01Plus(spi_inst_t* spi, uint csn, uint ce):
spi_(spi), csn_(csn), ce_(ce)
{
    spi_init(spi_, SPI_BAUDRATE);

    gpio_set_function(SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO_PIN, GPIO_FUNC_SPI);

    // NRF24L01+ config
    setNotChosen();
    setChosen();
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

void NRF24L01Plus::write_register(uint8_t reg, uint8_t data)
{
    // Command W_REGISTER is 001A AAAA.
    // We create it by performing a bitwise OR
    // of the command code (001) and the 5-bit argument (AAAAA)
    uint8_t cmd = 0b00100000 | (reg & 0b00011111);
    setChosen();

    // The process consists of 2 spi cycles.
    // First choose the register,
    spi_write_blocking(spi_, &cmd, 1);
    // then write the data
    spi_write_blocking(spi_, &data, 1);

    setNotChosen();
}

uint8_t NRF24L01Plus::read_register(uint8_t reg)
{
    uint8_t read_data;
    uint8_t cmd = 0b00011111 & reg;
    setChosen();
    
    // Choose the register
    spi_write_blocking(spi_, &cmd, 1);

    // Read the data
    // The 0xff is sent, because it is recognized as
    // a NOP command by the NRF24L01+ module.
    spi_read_blocking(spi_, 0xff, &read_data, 1);

    setNotChosen();

    return read_data;
}

void NRF24L01Plus::setCSN(bool isChosen) {
    gpio_put(csn_, isChosen);
}

void NRF24L01Plus::setChosen() {
    // The device is chosen when CSN = 0
    setCSN(0);
}

void NRF24L01Plus::setNotChosen() {
    // The device is NOT chosen when CSN = 1
    setCSN(1);
}

void NRF24L01Plus::setToTX() {
    // TX module, so set the bit nr 0 (LSB) to 0
    uint8_t reg_contents = read_register(0xff);
    reg_contents = reg_contents & 0b11111110;
    write_register(0xff, reg_contents);
}

void NRF24L01Plus::setToRX() {
    // RX module, so set the bit nr 0 (LSB) to 1
    uint8_t reg_contents = read_register(0xff);
    reg_contents = reg_contents | 0b00000001;
    write_register(0xff, reg_contents);
}