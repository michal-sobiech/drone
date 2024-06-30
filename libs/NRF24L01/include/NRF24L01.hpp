#pragma once
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <cstdio>

#define PAYLOAD_LEN 5

#define SPI_BAUDRATE 8000000

#define SPI_0 0
#define SPI_1 1

#define TX 0
#define RX 1

class NRF24L01
{
protected:
    // variables
    spi_inst_t* _spi;
    uint _vcc_pin;
    uint _ce_pin;
    uint csn_pin_;
    uint sck_pin_;
    uint mosi_pin_;
    uint miso_pin_;
    uint irq_pin_;
    bool mode_;

    // functions
    NRF24L01(bool default_mode);
    
    void configure();

    void _write_register(uint8_t reg, uint8_t* data, uint8_t size);
    void _write_register(uint8_t reg, uint8_t data);
    uint8_t _read_register(uint8_t reg);

    void _set_to_TX_state();
    void _setToRX();

    void _spi_write_one_byte(uint8_t data);
    uint8_t _spi_read_one_byte();

    void _set_CSN_high();
    void _set_CSN_low();
    void _set_CE_high();
    void _set_CE_low();
};