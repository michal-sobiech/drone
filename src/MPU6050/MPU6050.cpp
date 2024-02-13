#include "pico/stdlib.h"
#include "MPU6050.hpp"
#include "AngleReadings.hpp"


MPU6050::MPU6050() {
    i2c_ = i2c1;
    vin_pin_ = 8;
    sda_pin_ = 6;
    scl_pin_ = 7;

    // Enable I2C
    i2c_init(i2c_, 100 * 1000); // TODO 400 Hz
    gpio_set_function(sda_pin_, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin_, GPIO_FUNC_I2C);

    // Enable the VIN pin
    gpio_init(vin_pin_);
    gpio_set_dir(vin_pin_, GPIO_OUT);
    gpio_put(vin_pin_, 1); // TODO gpio_pull_up()??

    sleep_ms(1000);

    uint8_t data_to_send[2] = {0x6B, 0b10000000};
    i2c_write(data_to_send, 2);

    uint8_t who_am_i;
    uint8_t reg = 0x75;
    i2c_write(&reg, 1, true);
    i2c_read(&who_am_i, 1);
    printf("0x75: %d\r\n", unsigned(who_am_i));
}

AngleReadings MPU6050::measure_rotation() {
    // // The address of the first GYRO register is 0x43
    // uint8_t first_reg = 0x43;
    // uint8_t gyro_data[6];  
    // i2c_write(&first_reg, 1, true);
    // i2c_read(gyro_data, 6);
    // for (uint i = 0; i < 3; i++) {
    //     axis_rot[i] = gyro_data[2*i] << 8 + gyro_data[2*i + 1];
    // }
    // return;
}

// uint8_t MPU6050::read_reg(uint8_t reg) {
//     uint8_t sent_data[2] = {MPU6050_I2C_ADDRESS, reg};
//     uint8_t reg_contents;
//     i2c_write(&sent_data, 2, true);
//     i2c_read(&reg_contents, 1);
//     return reg_contents;
// }

// TODO inline or no inline??
inline void MPU6050::i2c_read(uint8_t r_data[], uint8_t len, bool no_stop) {
    i2c_read_blocking(i2c_, MPU6050_I2C_ADDRESS, r_data, len, no_stop);
}

// TODO inline or no inline??
inline void MPU6050::i2c_write(uint8_t w_data[], uint8_t len, bool no_stop) {
    i2c_write_blocking(i2c_, MPU6050_I2C_ADDRESS, w_data, len, no_stop);
}