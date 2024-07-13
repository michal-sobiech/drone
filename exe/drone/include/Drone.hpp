#include <array>
#include <cstdint>
#include <vector>

#include "NRF24L01RX.hpp"
#include "MPU6050.hpp"
#include "Engine.hpp"
#include "DroneMovement.hpp"
#include "EngineSpeedSetpoints.hpp"
#include "PID.hpp"

#include "EngineManager.hpp"


class Drone {
public:
    Drone(const DroneConfig& config);
    NRF24L01RX& get_transceiver();
    MPU6050& get_mpu();
private:
    EngineManager _engine_manager;
    NRF24L01RX _radio;
    MPU6050 _gyroscope_;
    const float weight_;

    void main_loop();
    DroneMovement get_desired_drone_movement();

    EngineSpeeds move(const DroneMovement &dm);
    EngineSpeeds move_x(float speed);
    EngineSpeeds move_y(float speed);
    EngineSpeeds move_z(float speed);
    EngineSpeeds calc_roll_engine_speeds(float ang_speed);
    EngineSpeeds calc_pitch_engine_speeds(float ang_speed);
    EngineSpeeds change_yaw(float ang_speed);
    RotationReadings measure_rotation();
}