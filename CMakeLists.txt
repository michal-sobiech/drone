cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(chadrone C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(libs/MPU6050)
add_subdirectory(libs/NRF24L01)
add_subdirectory(libs/pid)

add_subdirectory(exe/drone)
add_subdirectory(exe/controller)