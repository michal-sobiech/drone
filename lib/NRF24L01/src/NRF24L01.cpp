#include "NRF24L01.hpp"

#include <algorithm>
#include <cstdio>

#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "NRF24L01Config.hpp"


NRF24L01::NRF24L01(NRF24L01Config config) {
    _spi = config._spi;

    _ce_gpio = config.ce_gpio;
    _csn_gpio = config.csn_gpio;
    _irq_gpio = config.irq_gpio; 

    // SPI functions
    spi_init(_spi, config.spi_baudrate);
    gpio_set_function(config.sck_gpio, GPIO_FUNC_SPI);
    gpio_set_function(config.mosi_gpio, GPIO_FUNC_SPI);
    gpio_set_function(config.miso_gpio, GPIO_FUNC_SPI);

    gpio_init(_ce_gpio);
    gpio_set_dir(_ce_gpio, GPIO_OUT);

    gpio_init(_csn_gpio);
    gpio_set_dir(_csn_gpio, GPIO_OUT);

    set_CSN_high();

    main_setup(config.mode);
    auto_ack_setup();
    rf_setup(config.power_level, config.data_rate);
    frequency_setup(config.frequency_offset);

    sleep_ms(5 * 1000);

#ifdef DEBUG
    printf(
        "START 0x00: %d, 0x07: %d\r\n",
        read_register(0x00),
        read_register(0x07)
    );
#endif
}

void NRF24L01::main_setup(const NRF24L01Mode& mode) {

    set_CE_low();

    // Power on reset.
    // At least 10,3 ms, here rounded up to 11.
    sleep_ms(11);

    // Write to the config register (0x00):
    uint8_t config = 0b0000_0000;

    // Bit 0: PRIM_RX - choose between TX and RX.
    // TX - 0
    // RX - 1
    config |= (mode == NRF24L01Mode::TX) ? 0<<0 : 1<<0;

    // Bit 1: PWR_UP - power up.
    // Set it to 1 because we turn the module on.
    config |= 1<<1;

    // Bit 2: CRCO - CRC encoding scheme.
    // Leave as 0 because it seems not to hold much significance.

    // Bit 3:  EN_CRC - enable CRC.
    // Set to 1 because we want the CRC.
    config |= 1<<3;

    // Bits 4 - 6: MASK_MAX_RT, MASK_TX_DS and MASK_RX_DR - interrupts.
    // All enabled by leaving ass 0 because why not.

    // Bit 7: Reserved, must be 0.

    write_register(0x00, config);

    // Wait 1,5 ms after PWR_UP
    // sleep_us(1500);

    // uint8_t *RX_pipe_name = static_cast<uint8_t *>("PIPE0");
    // write_register(0x0a, RX_pipe_name, 5);

    // uint8_t *TX_pipe_name = static_cast<uint8_t *>("PIPE0");
    // write_register(0x0a, TX_pipe_name, 5);

    set_CE_low();
}

void NRF24L01::auto_ack_setup() {
    // Turn off auto ack
    write_register(0x01, 0);
}

void NRF24L01::frequency_setup(const uint8_t& frequency_offset) {
    static_assert(frequency_offset < 2<<7, "SAMPLE TEXT");
    write_register(0x05, frequency_offset);
}

void NRF24L01::rf_setup(
    const NRF24L01PowerLevel& power_level,
    const NRF24L01DataRate& data_rate
) {
    uint8_t settings = 0;

    // Bit 0: LNA_HCURR
    // Set it to its default value, 1
    settings |= 1<<0;

    // Bits 1 - 2: RF_PWR
    uint8_t rf_pwr;
    switch (power_level) {
        case NRF24L01PowerLevel::DB_MINUS_18:
        default:
            rf_pwr = 0b00;
            break;
        case NRF24L01PowerLevel::DB_MINUS_12:
            rf_pwr = 0b01;
            break;
        case NRF24L01PowerLevel::DB_MINUS_6:
            rf_pwr = 0b10;
            break;
        case NRF24L01PowerLevel::DB_0:
            rf_pwr = 0b11;
            break;
    }
    settings |= rf_pwr<<1;

    // Bit 3: RF_DR
    // Set to default, which is 1
    settings |= (data_rate == NRF24L01DataRate::MBPS_2) ? 1<<3 : 0;

    write_register(0x06, settings);
}

void payload_size_setup(uint8_t payload_size) {
    static_assert(payload_size < 2<<6, "SAMPLE TEXT");
    write_register(0x11, payload_size);
}

void NRF24L01::write_register(uint8_t reg, std::vector<uint8_t> buffer)
{
    // Command W_REGISTER is 001A AAAA.
    uint8_t reg_choice_command = 0b0010_0000;

    // Add the register address (5 bits)
    static_assert(reg < 2<<5, "SAMPLE TEXT");
    reg_choice_command |= (reg & 0b0001_1111);

    set_CSN_low();
    // The process consists of 2 spi cycles.
    // First choose the register,
    spi_write_blocking(_spi, &reg_choice_command, 1);
    // then write the data
    spi_write_blocking(_spi, buffer.data(), buffer.size());
    set_CSN_high();
}

void NRF24L01::write_register(uint8_t reg, uint8_t data) {
    write_register(reg, &data, 1);
}

uint8_t NRF24L01::read_register(uint8_t reg)
{
    // Command R_REGISTER is 000A AAAA
    uint8_t reg_choice_command = 0b0001_1111 & reg;
    uint8_t read_data;

    set_CSN_low();
    // Choose the register
    spi_write_blocking(_spi, &reg_choice_command, 1);
    // Read the data
    // The 0xff is sent because it is recognized as
    // a NOP command by the NRF24L01+ module.
    spi_read_blocking(_spi, 0xff, &read_data, 1);
    set_CSN_high();

    return read_data;
}

void NRF24L01::set_CSN_high() {
    gpio_put(_csn_gpio, 1);
}

void NRF24L01::set_CSN_low() {
    gpio_put(_csn_gpio, 0);
}

// void NRF24L01::spi_write_one_byte(uint8_t data) {
//     set_CE_high();
//     uint8_t test_data = 13;
//     // spi_write_blocking(_spi, &data, 1);
//     spi_write_blocking(_spi, &test_data, 1);
//     set_CE_low();
// }

// uint8_t NRF24L01::spi_read_one_byte() {
//     uint8_t read_data;
//     set_CE_high();
//     spi_read_blocking(_spi, 0xff, &read_data, 1);
//     set_CE_low();
//     return read_data;
// }

void NRF24L01::set_CE_high() {
    gpio_put(_ce_gpio, 1);
}

void NRF24L01::set_CE_low() {
    gpio_put(_ce_gpio, 0);
}

std::vector<uint8_t> const NRF24L01RX::receiveMessage() {
    // Requirements for going into the TX mode:
    // 1. PRIM_RX = 1 (already satisfied in the constructor)
    // 2. CE = 1
    // Then wait >= 130 us (RX Settling)

    // TODO

    // 2.
    set_CE_high();

    sleep_us(130);

    // TODO resetting RX_DR
    if (!data_received) {
        return;
    }
    // Get the received data using the R_RX_PAYLOAD
    // command (0110 0001)
    uint8_t command = 0b0110_0001;
    set_CSN_low();
    spi_write_blocking(_spi, &command, 1);
    spi_read_blocking(_spi, 0xff, received_data, PAYLOAD_LEN);
    set_CSN_high();

    // Reset RX_DR
    write_register(0x07, 0b01000000);

    set_CE_low();
}

void NRF24L01TX::sendMessage(const std::vector<uint8_t>& buffer) {
    // Requirements for going into the TX mode:
    // 1. Put the payload into the TX FIFO
    // 2. PRIM_RX = 0 (already satisfied)
    // 3. CE = 1 for >= 10 us
    // Then wait >= 130 us (TX Settling)
    // After that set CE to 0 (important!)

    // set_CE_low();

    // PWR_UP
    // write_register(0x00, read_register(0x00) | 0x00000010);
    sleep_us(1500);

    // Clear TX_DS
    write_register(0x07, 0b0010_0000);

    // Clear the TX FIFO
    uint8_t flush_TX_FIFO_cmd = 0b11100001;
    set_CSN_low();
    spi_write_blocking(_spi, &flush_TX_FIFO_cmd, 1);
    set_CSN_high();

    // 1.
    // W_TX_PAYLOAD command is 1010 0000
    uint8_t W_TX_cmd = 0b10100000;
    set_CSN_low();
    spi_write_blocking(_spi, &W_TX_cmd, 1);
    spi_write_blocking(_spi, data, PAYLOAD_LEN);
    set_CSN_high();

    bool tx_ds;

    // 3.
    set_CE_high();
    sleep_us(10);
    set_CE_low();

    while (true) {
        status_reg = read_register(0x07);
        tx_ds = (status_reg >> 5) & 1;
        if (tx_ds) {
            std::cout << "TX_DS was set to 1\r\n";
            break;
        }
    }

    printf("0x00: %d, 0x07: %d, 0x01: %d\r\n", read_register(0x00), read_register(0x07), read_register(0x01));

    // sleep_us(130);

}