#include <vector>
#include <array>
#include <algorithm>
#include <hardware/pio.h>
#include "Drone.hpp"
#include "NRF24L01RX.hpp"
#include "MPU6050.hpp"
#include "pin_map.hpp"
#include "DroneMovement.hpp"
#include "EngineSpeedSetpoints.hpp"


using uint = unsigned int;


Drone::Drone(float weight): weight_(weight) {
    const uint DRONE_SOC_METER_GPIO_NO = 26;
    const uint DRONE_SOC_METER_ADC_NO = 0;
    const uint DRONE_SOC_METER_MUX_SEL_H_GPIO_NO = 21;
    const uint DRONE_SOC_METER_MUX_SEL_L_GPIO_NO = 20;

    const uint FRONT_RIGHT_ENG_NO = 0;
    const uint FRONT_LEFT_ENG_NO = 1;
    const uint BACK_LEFT_ENG_NO = 2;
    const uint BACK_RIGHT_ENG_NO = 3;

    const uint ENG_PIO_NO = 0;

    const uint FRONT_RIGHT_ENG_PIN = 0;
    const uint FRONT_LEFT_ENG_PIN = 15;
    const uint BACK_LEFT_ENG_PIN = 16;
    const uint BACK_RIGHT_ENG_PIN = 28;

    const uint FRONT_RIGHT_ENG_SM = 0;
    const uint FRONT_LEFT_ENG_SM = 1;
    const uint BACK_LEFT_ENG_SM = 2;
    const uint BACK_RIGHT_ENG_SM = 3;

    const float DRONE_MASS = 0.25f;
    const float g_constant = 9.80665f;

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


void Drone::change_roll(float deg) {
    // Rotate around the X axis
    deg = std::clamp(deg, -90.0f, 90.0f);

    
}


void Drone::change_pitch(float deg) {
    // Rotate around the Y axis
    deg = std::clamp(deg, -90.0f, 90.0f);
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