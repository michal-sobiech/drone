cmake_minimum_required(VERSION 3.10)

project(MPU6050)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/MPU6050.cpp
)

add_library(mpu6050 STATIC ${SOURCES})

target_include_directories(mpu6050 include)