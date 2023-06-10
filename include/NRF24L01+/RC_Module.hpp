#include "hardware/spi.h"
#include <cstdint>

#define SPI_BAUDRATE 1000000
#define SPI_SCK_PIN 2
#define SPI_CSN_PIN 1
#define SPI_MOSI_PIN 3
#define SPI_MISO_PIN 4


class RC_Module
{
    public:
        RC_Module();
        RC_Module(spi_inst_t spi, uint csn, uint ce);
        void write_register(uint8_t reg, uint8_t data);
        uint8_t read_register();
    private:
        spi_inst_t spi;
        uint csn;
        uint ce;
}