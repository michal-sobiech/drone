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

class NRF24L01Plus
{
protected:
    // variables
    spi_inst_t* spi_;
    uint vcc_pin_;
    uint ce_pin_;
    uint csn_pin_;
    uint sck_pin_;
    uint mosi_pin_;
    uint miso_pin_;
    uint irq_pin_;
    bool mode_;

    // functions
    NRF24L01Plus(bool default_mode);
    
    void configure();

    void write_register(uint8_t reg, uint8_t* data, uint8_t size);
    void write_register(uint8_t reg, uint8_t data);
    uint8_t read_register(uint8_t reg);

    void set_to_TX_state();
    void setToRX();

    void spi_write_one_byte(uint8_t data);
    uint8_t spi_read_one_byte();

    void set_CSN_high();
    void set_CSN_low();
    void set_CE_high();
    void set_CE_low();
};