#include <vector>
#include <array>
#include <algorithm>
#include <cstdint>
#include <hardware/pio.h>
#include <cmath>

#include "Drone.hpp"
#include "DroneConfig.hpp"
#include "NRF24L01RX.hpp"
#include "MPU6050.hpp"
#include "pin_map.hpp"
#include "DroneMovement.hpp"
#include "EngineSpeeds.hpp"


Drone::Drone(
    const DroneConfig& config
){
    engine_manager_ = EngineManager();
    _radio = NRF24L01RX();
    gyroscope_ = MPU6050();
}


void Drone::main_loop() {
    RotationReadings rotation = mpu_.measure_rotation();
    float prev_roll_angle = rotation.roll;
    float prev_pitch_angle = rotation.pitch;

    while (true) {
        DroneMovement movement = get_desired_drone_movement();
        float dest_x_speed = movement.x_speed;
        float dest_y_speed = movement.y_speed;

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

        EngineSpeeds roll_speeds = get_roll_engine_speeds(roll_control_signal);
        EngineSpeeds pitch_speeds = calc_pitch_engine_speeds(pitch_control_signal);
    
        EngineSpeeds final_speeds = roll_speeds + pitch_speeds;
        set_engines_speeds(final_speeds);
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

void Drone::set_engines_speed(const EngineSpeeds &speeds) {
}


EngineSpeeds Drone::get_roll_engine_speeds(float ang_speed) {
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


EngineSpeeds Drone::calc_pitch_engine_speeds(float ang_speed) {
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


RotationReadings Drone::measure_rotation() {
    return mpu_.measure_rotation();
}


float Drone::get_weight() {

}