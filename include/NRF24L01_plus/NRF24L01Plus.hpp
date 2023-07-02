#pragma once
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <cstdio>

#define SPI_BAUDRATE 1000000

#define SPI_0 0
#define SPI_1 1

#define TX 0
#define RX 1

class NRF24L01Plus
{
public:
    NRF24L01Plus();
    NRF24L01Plus(bool default_mode);
    void setChosen();
    void setNotChosen();
    void sendByte(uint8_t data);
    uint8_t receiveByte();
private:
    spi_inst_t* spi_;
    uint vcc_pin_;
    uint ce_pin_;
    uint csn_pin_;
    uint sck_pin_;
    uint mosi_pin_;
    uint miso_pin_;
    uint irq_pin_;
    bool mode_;
    void setCSN(bool isChosen);
    void write_register(uint8_t reg, uint8_t data);
    uint8_t read_register(uint8_t reg);
    void setToTX();
    void setToRX();
    void spi_write_one_byte(uint8_t data);
    uint8_t spi_read_one_byte();
};