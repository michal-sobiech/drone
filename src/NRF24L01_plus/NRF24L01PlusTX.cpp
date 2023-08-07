#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "NRF24L01PlusTX.hpp"

NRF24L01PlusTX::NRF24L01PlusTX() : NRF24L01Plus(TX) {
}

void NRF24L01PlusTX::sendMessage(uint8_t data[]) {
    // Requirements for going into the TX mode:
    // 1. Put the payload into the TX FIFO
    // 2. PRIM_RX = 0 (already satisfied in the constructor)
    // 3. CE = 1
    // Then wait >= 130 us (TX Settling)
    // After that set CE to 0 (important!)

    // Clear the TX FIFO
    uint8_t flush_TX_FIFO_cmd = 0b11100001;
    set_CSN_low();
    spi_write_blocking(spi_, &flush_TX_FIFO_cmd, 1);
    set_CSN_high();

    // uint8_t status_reg = read_register(0x07);
    // printf("Status reg: %d\r\n", status_reg);

    // 1.
    // W_TX_PAYLOAD command is 1010 0000
    uint8_t W_TX_cmd = 0b10100000;
    set_CSN_low();
    spi_write_blocking(spi_, &W_TX_cmd, 1);
    spi_write_blocking(spi_, data, PAYLOAD_LEN);
    set_CSN_high();

    // 3.
    set_CE_high();

    sleep_us(130);
    sleep_us(500);

    set_CE_low();

    // uint8_t reg = read_register(0x00); 
    // printf("Reg: %d\r\n", reg);
}