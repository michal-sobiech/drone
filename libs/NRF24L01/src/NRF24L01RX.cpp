#include "NRF24L01RX.hpp"

NRF24L01RX::NRF24L01RX() : NRF24L01(RX) {
    uint8_t status_reg = read_register(0x00);
    printf("reg: %d\r\n", status_reg);
}

void NRF24L01RX::receiveMessage(uint8_t received_data[]) {
    // Requirements for going into the TX mode:
    // 1. PRIM_RX = 1 (already satisfied in the constructor)
    // 2. CE = 1
    // Then wait >= 130 us (RX Settling)

    // 2.
    set_CE_high();

    sleep_us(130);

    // Check the RX_DR bit to see if
    // the receiver caught anything.
    uint8_t status_reg = read_register(0x07);
    bool data_received = (status_reg >> 6) & 1;
    printf("0x07 register: %d\r\n", status_reg);
    // printf("Was data received? %s\r\n", data_received ? "yes" : "no");

    // TODO resetting RX_DR
    if (!data_received) {
        return;
    }
    // Get the received data using the R_RX_PAYLOAD
    // command (0110 0001)
    uint8_t cmd = 0b01100001;
    uint8_t sent_data = 0xff;
    set_CSN_low();
    spi_write_blocking(_spi, &cmd, 1);
    spi_read_blocking(_spi, sent_data, received_data, PAYLOAD_LEN);
    set_CSN_high();

    // Reset RX_DR
    write_register(0x07, 0b01000000);

    status_reg = read_register(0x07);

    set_CE_low();
} 