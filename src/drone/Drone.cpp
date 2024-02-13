#include <vector>
#include <array>
#include <hardware/pio.h>
#include "Drone.hpp"
#include "NRF24L01RX.hpp"
#include "MPU6050.hpp"
#include "pin_map.hpp"


using uint = unsigned int;


Drone::Drone() {

    // Engine setup
    const PIO engine_pio = (ENG_PIO_NO == 0) ? pio0 : pio1;
    const std::array<GpioPin, 4> engine_pins{
        FRONT_RIGHT_ENG_PIN,
        FRONT_LEFT_ENG_PIN,
        BACK_LEFT_ENG_PIN,
        BACK_RIGHT_ENG_PIN
    };
    const std::array<uint, 4> sm_ids{
        FRONT_RIGHT_ENG_SM,
        FRONT_LEFT_ENG_SM,
        BACK_LEFT_ENG_SM,
        BACK_RIGHT_ENG_SM
    };

    engine_setup(engine_pio, engine_pins, sm_ids);

    // NRF24L01+ setup
    // transceiver_ = NRF24L01RX();

    mpu_ = MPU6050();
}


NRF24L01RX& Drone::get_transceiver() {
    return transceiver_;
}


MPU6050& Drone::get_mpu() {
    return mpu_;
}


void Drone::move(DroneMovement &drone_movement) {
    ;
}


Engine& Drone::get_engine(EnginePosition engine_pos) {
    return engines_[engine_pos];
}


void Drone::set_engines_speed(const std::array<const float, 4> &speeds) {
    /*
    The index corresponds to the engine.
    */
    for (const float &s : speeds) {
        
    }
}

void Drone::engine_setup(
    const PIO& pio,
    const std::array<GpioPin, 4>& engine_pins, 
    const std::array<uint, 4>& sm_ids
){
    for (uint i = 0; i < engine_pins.size(); i++) {
        engines_[i] = Engine(pio, engine_pins[i], sm_ids[i]);
    }
}