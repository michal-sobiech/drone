cmake_minimum_required(VERSION 3.13)

project(drone C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(drone
    src/drone/Drone.cpp
    src/drone/main.cpp
    src/drone/drone_soc_meter/DroneSocMeter.cpp
    src/drone/engine/Engine.cpp
)

target_include_directories(drone PUBLIC
    include/drone
    include/drone/drone_soc_meter
    include/drone/engine
)

target_link_libraries(drone
    pico_stdlib

    hardware_pio
    hardware_spi
    hardware_adc
    hardware_i2c

    mpu6050
    NRF24L01
    pid
)

pico_generate_pio_header(drone
    ${CMAKE_CURRENT_LIST_DIR}/src/drone/dshot.pio
)

pico_enable_stdio_usb(${DRONE_TARGET} 1)
pico_enable_stdio_uart(${DRONE_TARGET} 1)

pico_add_extra_outputs(${DRONE_TARGET})