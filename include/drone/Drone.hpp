#include "NRF24L01PlusRX.hpp"
#include "MPU6050.hpp"
#include "Engine.hpp"
#include <vector>

class Drone
{
public:
    Drone();
    NRF24L01PlusRX& get_transceiver();
    MPU6050& get_mpu();
private:
    std::vector<Engine> engines_;
    NRF24L01PlusRX transceiver_;
    MPU6050 mpu_;
};