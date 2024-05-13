cmake_minimum_required(VERSION 3.10)

include(pico_sdk_import.cmake)

project(MPU6050)

pico_sdk_init()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/MPU6050.cpp
)

add_library(mpu6050 STATIC ${SOURCES})

target_include_directories(mpu6050 PUBLIC include)

target_link_libraries(mpu6050
    pico_stdlib

    hardware_i2c
)