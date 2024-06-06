cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(drone C CXX ASM)

pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(TARGET controller)
add_executable(${TARGET}
    src/drone_soc_meter/DroneSocMeter.cpp
    src/engine/Engine.cpp
    src/Drone.cpp
    src/main.cpp
)

target_include_directories(${TARGET} PUBLIC
    include
    include/drone_movement
    include/drone_soc_meter
    include/engine
)

target_link_libraries(${TARGET}
    pico_stdlib

    hardware_spi
    hardware_adc

    adc_unit
    four_channel_mux
    mpu6050
    NRF24L01
    pid
)

pico_enable_stdio_usb(${TARGET} 1)
pico_enable_stdio_uart(${TARGET} 1)

pico_add_extra_outputs(${TARGET})