#include <vector>
#include <array>
#include <algorithm>
#include <cstdint>
#include <hardware/pio.h>
#include <cmath>

#include "Drone.hpp"
#include "NRF24L01RX.hpp"
#include "MPU6050.hpp"
#include "pin_map.hpp"
#include "DroneMovement.hpp"
#include "EngineSpeeds.hpp"


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


void Drone::main_loop() {
    RotationReadings rotation = mpu_.measure_rotation();
    float prev_roll_angle = rotation.roll;
    float prev_pitch_angle = rotation.pitch;

    while (true) {
        DroneMovement dm = get_desired_drone_movement();
        float dest_x_speed = dm.x_speed;
        float dest_y_speed = dm.y_speed;

        // TEMPORARY
        float desired_roll_angle = dest_x_speed;
        float desired_pitch_angle = dest_y_speed;
        
        rotation = mpu_.measure_rotation();
        float current_roll_angle = rotation.roll;
        float current_pitch_angle = rotation.pitch;

        float roll_control_signal = roll_pid_.calc_u(
            desired_roll_angle,
            prev_roll_angle
        );

        float pitch_control_signal = pitch_pid_.calc_u(
            desired_pitch_angle,
            prev_pitch_angle
        );

        EngineSpeeds roll_signals = calc_roll_engine_signals(roll_control_signal);
        EngineSpeeds pitch_signals = calc_pitch_engine_signals(pitch_control_signal);
    }
}


EngineSpeeds Drone::move_x(float speed) {
}


EngineSpeeds Drone::move_y(float speed) {
}


EngineSpeeds Drone::move_z(float speed) {
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


void Drone::set_engines_speed(const EngineSpeeds &speeds) {
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


EngineSpeeds Drone::move(DroneMovement &dm) {
    float fr_speed = 0;
    float fl_speed = 0;
    float bl_speed = 0;
    float br_speed = 0;

    // float rotation = 

    // X movement
    move_x(dm.x_speed)

    // Y movement
    fr_speed += dm.y;
    fl_speed += dm.y;
    bl_speed += dm.y;
    br_speed += dm.y;

    // Z movement
    

    return EngineSpeeds{
        fr_speed,
        fl_speed,
        bl_speed,
        br_speed
    };
}


EngineSpeeds Drone::calc_roll_engine_signals(float ang_speed) {
    // Rotate around the X axis
    if (ang_speed >= 0) {
        // Tilt forward
        return EngineSpeeds{
            .fr_speed = 0,
            .fl_speed = 0,
            .bl_speed = ang_speed,
            .br_speed = ang_speed
        };
    }
    else {
        // Tilt backward
        return EngineSpeeds{
            .fr_speed = ang_speed,
            .fl_speed = ang_speed,
            .bl_speed = 0,
            .br_speed = 0
        };
    }
}


EngineSpeeds Drone::calc_pitch_engine_signals(float ang_speed) {
    // Rotate around the Y axis
    if (ang_speed >= 0) {
        // Tilt right
        return EngineSpeeds{
            .fr_speed = 0,
            .fl_speed = ang_speed,
            .bl_speed = ang_speed,
            .br_speed = 0
        };
    }
    else {
        // Tilt left
        return EngineSpeeds{
            .fr_speed = ang_speed,
            .fl_speed = 0,
            .bl_speed = 0,
            .br_speed = ang_speed
        };
    }
}


EngineSpeeds Drone::change_yaw(float ang_speed) {
    // Rotate around the Z axis
    if (ang_speed >= 0) {
        // Turn right
        return EngineSpeeds{
            .fr_speed = 0,
            .fl_speed = ang_speed,
            .bl_speed = 0,
            .br_speed = ang_speed
        };
    }
    else {
        // Turn left
        return EngineSpeeds{
            .fr_speed = ang_speed,
            .fl_speed = 0,
            .bl_speed = ang_speed,
            .br_speed = 0
        };
    }
}


std::array<float, 3> Drone::measure_angle() {
    // return mpu_.measure_rotation();
    ;
}


float Drone::get_weight() {

}