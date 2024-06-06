#include <cstdint>


struct Nrf24l01Config {
    uint8_t ce_gpio_no;
    uint8_t csn_gpio_no;
    uint8_t sck_gpio_no;
    uint8_t mosi_gpio_no;
    uint8_t miso_gpio_no;
    uint8_t irq_gpio_no;
};