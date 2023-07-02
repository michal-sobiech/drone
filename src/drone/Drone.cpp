#include <vector>
#include <hardware/pio.h>
#include "NRF24L01Plus.hpp"
#include "Drone.hpp"

Drone::Drone() {

    // Engine setup
    const PIO pio = pio0;
    const std::vector<unsigned int> engine_pins{0, 15, 16, 28};
    const std::vector<unsigned int> sm_ids{0, 1, 2, 3};

    engines_ = std::vector<Engine>();
    for (unsigned int i = 0; i < engine_pins.size(); i++) {
        engines_.push_back(Engine(pio, engine_pins[i], sm_ids[i]));
    }

    // NRF24L01+ setup
    const bool default_mode = RX;
    transceiver_ = NRF24L01Plus(default_mode);
}

NRF24L01Plus& Drone::get_transceiver() {
    return transceiver_;
}