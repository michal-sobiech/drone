#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <cstdio>

#define SPI_BAUDRATE 1000000
#define SPI_SCK_PIN 2
#define SPI_CSN_PIN 1
#define SPI_MOSI_PIN 3
#define SPI_MISO_PIN 4

#define TX 0
#define RX 1

class NRF24L01Plus
{
public:
    NRF24L01Plus();
    NRF24L01Plus(spi_inst_t* spi, uint csn, uint ce, bool mode);
    void write_register(uint8_t reg, uint8_t data);
    uint8_t read_register(uint8_t reg);
    void setChosen();
    void setNotChosen();
    void setToTX();
    void setToRX();
private:
    spi_inst_t* spi_;
    uint csn_;
    uint ce_;
    bool mode_;
    void setCSN(bool isChosen);
};