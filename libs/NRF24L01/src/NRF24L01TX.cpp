#include <iostream>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "NRF24L01TX.hpp"

NRF24L01TX::NRF24L01TX() : NRF24L01(TX) {
    printf("0x00: %d, 0x07: %d\r\n", read_register(0x00), read_register(0x07));

    // Set TX_ADDR
    uint8_t tx_addr_size = 5;
    uint8_t tx_addr[tx_addr_size] = {'P', 'I', 'P', 'E', '0'};
    write_register(0x10, tx_addr, tx_addr_size);
}

void NRF24L01TX::sendMessage(uint8_t data[]) {
    // Requirements for going into the TX mode:
    // 1. Put the payload into the TX FIFO
    // 2. PRIM_RX = 0 (already satisfied)
    // 3. CE = 1 for >= 10 us
    // Then wait >= 130 us (TX Settling)
    // After that set CE to 0 (important!)

    // set_CE_low();

    std::cout << "NEW MESSAGE TRANSMIT PROCESS\r\n";
    uint8_t status_reg;

    // PWR_UP
    // write_register(0x00, read_register(0x00) | 0x00000010);
    sleep_us(1500);

    // Clear TX_DS
    write_register(0x07, 0b00100000);

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