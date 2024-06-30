#pragma once

#include <cstdio>

#include "hardware/i2c.h"
#include "RotationReadings.hpp"

#define MPU6050_I2C_ADDRESS 0x68


class MPU6050 {
public:
    MPU6050();
    RotationReadings measure_rotation();
    bool passes_self_tests();
private:
    i2c_inst_t* i2c_;
    uint _vin_pin;
    uint _sda_pin;
    uint _scl_pin;
    
    uint8_t read_reg(uint8_t reg);
    void i2c_read(uint8_t r_data[], uint8_t len, bool no_stop = false);
    void i2c_write(uint8_t w_data[], uint8_t len, bool no_stop = false);
};