#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <cstdio>
#include <algorithm>
#include "NRF24L01Plus.hpp"

// Max 125, because 2525 - 2400
#define MAX_CHANNEL_FREQ_OFFSET 125

NRF24L01Plus::NRF24L01Plus(bool default_mode): mode_(default_mode)
{

    // TODO customization
    spi_ = spi0;
    vcc_pin_ = 4;
    ce_pin_ = 5;
    csn_pin_ = 1;
    sck_pin_ = 2;
    mosi_pin_ = 3;
    miso_pin_ = 0;
    // irq_pin_ = ;     

    // SPI functions
    spi_init(spi_, SPI_BAUDRATE);

    gpio_set_function(sck_pin_, GPIO_FUNC_SPI);
    gpio_set_function(mosi_pin_, GPIO_FUNC_SPI);
    gpio_set_function(miso_pin_, GPIO_FUNC_SPI);

    gpio_init(vcc_pin_);
    gpio_init(ce_pin_);
    gpio_init(csn_pin_);

    gpio_set_dir(vcc_pin_, GPIO_OUT);
    gpio_set_dir(ce_pin_, GPIO_OUT);
    gpio_set_dir(csn_pin_, GPIO_OUT);

    // Enable the power pin
    gpio_put(vcc_pin_, 1);

    set_CE_low();
    set_CSN_high();

    configure();

    sleep_ms(5 * 1000);
    printf("START 0x00: %d, 0x07: %d\r\n", read_register(0x00), read_register(0x07));

}

void NRF24L01Plus::configure() {

    set_CSN_high();
    set_CE_low();

    sleep_ms(11); // 10,3 ms at least

    // Write to the config register (0x00):
    // bit 0 is RX or TX, we dont initially set this one
    // bit 1 is power up, set it to 1 because we turn the module on
    // bit 2 is CRC encoding scheme, set to 0 because it seems to not hold much significance 
    // bit 3 is the CRC, set to 1 because we want the CRC
    // bits 4 - 6 are interrupts, all enabled by setting to 0 bc why not
    // bit 7 must be 0
    uint8_t config_settings = 0b01111010;
    // Bit 0
    config_settings = config_settings + mode_;

    write_register(0x00, config_settings);
    // Wait 1,5 ms after PWR_UP
    sleep_us(1500);

    uint8_t reg = read_register(0x00); 

    // Turn off auto ack
    write_register(0x01, 0b00000000);

    // Channel
    uint8_t channel_freq = 60;
    // The frequency has an upper bound
    write_register(0x05, std::max<uint8_t>(channel_freq, MAX_CHANNEL_FREQ_OFFSET));

    uint8_t* RX_pipe_name = (uint8_t*)"PIPE0";
    write_register(0x0a, RX_pipe_name, 5);

    uint8_t* TX_pipe_name = (uint8_t*)"PIPE0";
    write_register(0x0a, TX_pipe_name, 5);

    // How many bytes RX can receive
    write_register(0x11, PAYLOAD_LEN);

    set_CE_low();
    set_CSN_high();
}

void NRF24L01Plus::write_register(uint8_t reg, uint8_t data[], uint8_t size)
{
    // Command W_REGISTER is 001A AAAA.
    // We create it by performing a bitwise OR
    // of the command code (001) and the 5-bit argument (AAAAA)
    uint8_t reg_choice_cmd = 0b00100000 | (reg & 0b00011111);

    set_CSN_low();
    // The process consists of 2 spi cycles.
    // First choose the register,
    spi_write_blocking(spi_, &reg_choice_cmd, 1);
    // then write the data
    spi_write_blocking(spi_, data, size);
    set_CSN_high();
}

void NRF24L01Plus::write_register(uint8_t reg, uint8_t data) {
    write_register(reg, &data, 1);
}

uint8_t NRF24L01Plus::read_register(uint8_t reg)
{
    // Command R_REGISTER is 000A AAAA
    uint8_t reg_choice_cmd = 0b00011111 & reg;
    uint8_t read_data;

    set_CSN_low();
    // Choose the register
    spi_write_blocking(spi_, &reg_choice_cmd, 1);
    // Read the data
    // The 0xff is sent because it is recognized as
    // a NOP command by the NRF24L01+ module.
    spi_read_blocking(spi_, 0xff, &read_data, 1);
    set_CSN_high();

    return read_data;
}

void NRF24L01Plus::set_CSN_high() {
    gpio_put(csn_pin_, 1);
}

void NRF24L01Plus::set_CSN_low() {
    gpio_put(csn_pin_, 0);
}

// void NRF24L01Plus::spi_write_one_byte(uint8_t data) {
//     set_CE_high();
//     uint8_t test_data = 13;
//     // spi_write_blocking(spi_, &data, 1);
//     spi_write_blocking(spi_, &test_data, 1);
//     set_CE_low();
// }

// uint8_t NRF24L01Plus::spi_read_one_byte() {
//     uint8_t read_data;
//     set_CE_high();
//     spi_read_blocking(spi_, 0xff, &read_data, 1);
//     set_CE_low();
//     return read_data;
// }

void NRF24L01Plus::set_CE_high() {
    gpio_put(ce_pin_, 1);
}

void NRF24L01Plus::set_CE_low() {
    gpio_put(ce_pin_, 0);
}