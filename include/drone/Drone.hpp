#include <vector>
#include <array>

#include "NRF24L01RX.hpp"
#include "MPU6050.hpp"
#include "Engine.hpp"
#include "DroneMovement.hpp"
#include "EngineSpeedSetpoints.hpp"


// The engines are numbered like graph quarants
using EnginePosition = unsigned int;
#define FRONT_RIGHT 0
#define FRONT_LEFT 1
#define BACK_LEFT 2
#define BACK_RIGHT 3


class Drone {
public:
    Drone(
        unsigned int fr_engine_pin,
        unsigned int fl_engine_pin, 
        unsigned int bl_engine_pin,
        unsigned int br_engine_pin,
        float weight,
        unsigned int engines_pio_no
    );
    NRF24L01RX& get_transceiver();
    MPU6050& get_mpu();
private:
    std::array<Engine, 4> engines_;
    NRF24L01RX transceiver_;
    MPU6050 mpu_;
    const float weight_;

    void engine_setup(
        const PIO& pio,
        const std::array<GpioPin, 4>& engine_pins, 
        const std::array<uint, 4>& sm_ids
    );

    Engine& get_engine(EnginePosition engine_pos);
    void set_engines_speed(const EngineSpeedSetpoints &speeds);
    EngineSpeedSetpoints move(DroneMovement &dm);  
    float get_weight();
    void move_x(float x);
    void move_y(float y);
    void move_z(float z);
    EngineSpeedSetpoints Drone::change_roll(
        float deg,
        float min_deg = -45.0f,
        float max_deg = 45.0f
    );
    EngineSpeedSetpoints Drone::change_pitch(
        float deg,
        float min_deg,
        float max_deg
    );
    EngineSpeedSetpoints change_yaw(float ang_speed);
    std::array<float, 3> measure_angle();
};