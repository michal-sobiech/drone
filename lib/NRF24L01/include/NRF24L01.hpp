#pragma once

#include <cstdio>
#include <memory>

#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "types.hpp"
#include "Nrf24l01Config.hpp"

#define SPI_BAUDRATE 8000000

#define SPI_0 0
#define SPI_1 1

#define TX 0
#define RX 1

class NRF24L01 {
protected:
    const spi_inst_t *_spi;

    const GpioNo _ce_gpio;
    const GpioNo _csn_gpio;
    const GpioNo _irq_gpio;

    NRF24L01(NRF24L01Config config);

    void main_setup(const NRF24L01Modem& mode);
    void auto_ack_setup();
    void rf_setup(
        const NRF24L01PowerLevel& power_level,
        const NRF24L01DataRate& data_rate
    );
    void frequency_setup(uint8_t frequency_offset);
    void payload_size_setup(uint8_t payload_size);

    void const _write_register(const uint8_t& reg, const std::vector<uint8_t>& data);
    void const _write_register(const uint8_t& reg, const uint8_t& data);
    uint8_t const _read_register(const uint8_t& reg);

    void _set_to_TX();
    void _set_to_RX();

    void const _spi_write_one_byte(uint8_t data);
    uint8_t const _spi_read_one_byte();

    void _set_CSN_high();
    void _set_CSN_low();
    void _set_CE_high();
    void _set_CE_low();

    std::vector<uint8_t> const receiveMessage();
    void const sendMessage(std::vector<uint8_t> data);
};