#pragma once

#include <memory>

#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "types.hpp"

enum NRF24L01Mode {
    TX,
    RX
};

enum NRF24L01PowerLevel {
    DB_MINUS_18,
    DB_MINUS_12,
    DB_MINUS_6,
    DB_0
}

enum NRF24L01DataRate {
    MBPS_1,
    MBPS_2
}

struct NRF24L01Config {
    const spi_inst_t *spi;

    const uint spi_baudrate;

    const NRF24L01Mode initial_mode;

    const NRF24L01PowerLevel power_level;

    const NRF24L01DataRate data_rate;

    const uint8_t frequency_offset;

    const GpioNo ce_gpio;
    const GpioNo csn_gpio;
    const GpioNo sck_gpio;
    const GpioNo mosi_gpio;
    const GpioNo miso_gpio;
    const GpioNo irq_gpio;
};