#include "NRF24L01PlusRX.hpp"

NRF24L01PlusRX::NRF24L01PlusRX() : NRF24L01Plus(RX) {}

void NRF24L01PlusRX::receiveMessage(uint8_t received_data[]) {
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
    // printf("Was data received? %s\r\n", data_received ? "yes" : "no");
    printf("Status reg: %d\r\n", status_reg);
    // TODO resetting RX_DR
    if (!data_received) {
        return;
    }
    // Get the received data using the R_RX_PAYLOAD
    // command (0110 0001)
    uint8_t cmd = 0b01100001;
    uint8_t sent_data = 0xff;
    set_CSN_low();
    spi_write_blocking(spi_, &cmd, 1);
    spi_read_blocking(spi_, sent_data, received_data, PAYLOAD_LEN);
    set_CSN_high();

    // Reset RX_DR
    write_register(0x07, 0b01000000);

    status_reg = read_register(0x07);
    printf("Status reg: %d\r\n", status_reg);

    set_CE_low();
} 