#include "Drone.hpp"
#include "NRF24L01PlusRX.hpp"
#include "MPU6050.hpp"
#include <vector>
#include <hardware/pio.h>

Drone::Drone() {

    // Engine setup
    const PIO pio = pio0;
    const std::vector<unsigned int> engine_pins{0, 15, 16, 28};
    const std::vector<unsigned int> sm_ids{0, 1, 2, 3};

    // engines_ = std::vector<Engine>();
    // for (unsigned int i = 0; i < engine_pins.size(); i++) {
    //     engines_.push_back(Engine(pio, engine_pins[i], sm_ids[i]));
    // }

    // NRF24L01+ setup
    // transceiver_ = NRF24L01PlusRX();

    mpu_ = MPU6050();
}

NRF24L01PlusRX& Drone::get_transceiver() {
    return transceiver_;
}

MPU6050& Drone::get_mpu() {
    return mpu_;
}