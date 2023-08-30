#pragma once
#include <cstdio>
#include "hardware/i2c.h"
#define MPU6050_I2C_ADDRESS 0x68

class MPU6050 {
public:
    MPU6050();
    void get_3_axis_rotation(uint16_t* axis_rot);
    bool passes_self_tests();
private:
    i2c_inst_t* i2c_;
    uint vin_pin_;
    uint sda_pin_;
    uint scl_pin_;
    
    uint8_t read_reg(uint8_t reg);
    void i2c_read(uint8_t r_data[], uint8_t len, bool no_stop = false);
    void i2c_write(uint8_t w_data[], uint8_t len, bool no_stop = false);
    // bool passes_
};