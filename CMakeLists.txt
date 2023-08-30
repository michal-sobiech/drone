cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(drone C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# Common files
file(GLOB_RECURSE NRF24L01_plus_SRC_FILES src/NRF24L01_plus/*.cpp)
file(GLOB_RECURSE MPU6050_SRC_FILES src/MPU6050/*.cpp)

# The main module
file(GLOB_RECURSE PROJECT_SRC_FILES src/drone/*.cpp)
add_executable(${PROJECT_NAME}
    ${PROJECT_SRC_FILES}
    ${NRF24L01_plus_SRC_FILES}
    ${MPU6050_SRC_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    include/drone
    include/drone/engine
    include/NRF24L01_plus
    include/MPU6050
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_pio
    hardware_spi
    hardware_adc
    hardware_i2c
)

pico_generate_pio_header(${PROJECT_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/drone/dshot.pio
)

pico_enable_stdio_usb(drone 1)
pico_enable_stdio_uart(drone 1)

pico_add_extra_outputs(drone)

# Controller
set(CONTROLLER_TARGET controller)
file(GLOB_RECURSE CONTROLLER_SRC_FILES src/controller/*.cpp)
add_executable(${CONTROLLER_TARGET}
    ${CONTROLLER_SRC_FILES}
    ${NRF24L01_plus_SRC_FILES}
    src/joystick/Joystick.cpp
    src/adc_gpio/AdcGpio.cpp
)
target_include_directories(${CONTROLLER_TARGET}
    PUBLIC
    include/controller
    include/NRF24L01_plus
    include/joystick
    include/adc_gpio
)
target_link_libraries(${CONTROLLER_TARGET}
    pico_stdlib
    hardware_spi
    hardware_adc
)

pico_enable_stdio_usb(${CONTROLLER_TARGET} 1)
pico_enable_stdio_uart(${CONTROLLER_TARGET} 1)

pico_add_extra_outputs(${CONTROLLER_TARGET})