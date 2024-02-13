#include <vector>
#include <array>
#include <algorithm>
#include <cstdint>
#include <hardware/pio.h>
#include <math.h>

#include "Drone.hpp"
#include "NRF24L01RX.hpp"
#include "MPU6050.hpp"
#include "pin_map.hpp"
#include "DroneMovement.hpp"
#include "EngineSpeedSetpoints.hpp"
#include "PID.hpp"


Drone::Drone(
    uint fr_engine_pin,
    uint fl_engine_pin, 
    uint bl_engine_pin,
    uint br_engine_pin,
    float weight,
    uint engines_pio_no):
    weight_(weight)
{

    // Engine setup
    const PIO engine_pio = (engines_pio_no == 0) ? pio0 : pio1;
    const std::array<GpioPin, 4> engine_pins{
        fr_engine_pin,
        fl_engine_pin,
        bl_engine_pin,
        br_engine_pin
    };
    const std::array<uint, 4> sm_ids{0, 1, 2, 3};
    engine_setup(engine_pio, engine_pins, sm_ids);

    // Transceiver setup
    transceiver_ = NRF24L01RX();

    // Gyroscope setup
    mpu_ = MPU6050();
}


NRF24L01RX& Drone::get_transceiver() {
    return transceiver_;
}


MPU6050& Drone::get_mpu() {
    return mpu_;
}


Engine& Drone::get_engine(EnginePosition engine_pos) {
    return engines_[engine_pos];
}


void Drone::set_engines_speed(const EngineSpeedSetpoints &speeds) {
    ;
}

void Drone::engine_setup(
    const PIO& pio,
    const std::array<GpioPin, 4>& engine_pins, 
    const std::array<uint, 4>& sm_ids
){
    for (uint i = 0; i < engine_pins.size(); i++) {
        engines_[i] = Engine(
            pio,
            engine_pins[i],
            sm_ids[i],
            PID()
        );
    }
}


EngineSpeedSetpoints Drone::move(DroneMovement &dm) {
    float fr_speed = 0;
    float fl_speed = 0;
    float bl_speed = 0;
    float br_speed = 0;

    // float rotation = 

    // X movement

    // Y movement
    fr_speed += dm.y;
    fl_speed += dm.y;
    bl_speed += dm.y;
    br_speed += dm.y;

    // Z movement
    

    return EngineSpeedSetpoints{
        fr_speed,
        fl_speed,
        bl_speed,
        br_speed
    };
}


EngineSpeedSetpoints Drone::change_roll(
    float deg,
    float min_deg,
    float max_deg
) {
    // Rotate around the X axis
    deg = std::clamp(deg, min_deg, max_deg);

    float rotation_percent = abs(deg / 90.0f);

    float fr_speed;
    float fl_speed;
    float bl_speed;
    float br_speed;

    if (rotation_percent >= 0) {
        fr_speed = 0;
        fl_speed = 0;
        bl_speed = rotation_percent;
        br_speed = rotation_percent;
    }
    else {
        fr_speed = rotation_percent;
        fl_speed = rotation_percent;
        bl_speed = 0;
        br_speed = 0;
    }

    return EngineSpeedSetpoints{
        fr_speed,
        fl_speed,
        bl_speed,
        br_speed
    };
}


EngineSpeedSetpoints Drone::change_pitch(
    float deg,
    float min_deg,
    float max_deg
) {
    // Rotate around the Y axis
    deg = std::clamp(deg, min_deg, max_deg);

    float rotation_percent = abs(deg / 90.0f);

    float fr_speed = 0;
    float fl_speed = 0;
    float bl_speed = rotation_percent;
    float br_speed = rotation_percent;

    return EngineSpeedSetpoints{
        fr_speed,
        fl_speed,
        bl_speed,
        br_speed
    };
}


void Drone::change_yaw(float deg) {
    // Rotate around the Z axis
}


std::array<float, 3> Drone::measure_angle() {
    // return mpu_.measure_rotation();
    ;
}


float Drone::get_weight() {

}