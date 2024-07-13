cmake_minimum_required(VERSION 3.10)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(MPU6050)

pico_sdk_init()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/MPU6050.cpp
)

set(TARGET mpu6050)
add_library(${TARGET} STATIC ${SOURCES})

target_include_directories(${TARGET} PUBLIC include)

target_link_libraries(${TARGET}
    pico_stdlib

    hardware_i2c
)