cmake_minimum_required(VERSION 3.13)

project(drone C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CONTROLLER_TARGET controller)
add_executable(${CONTROLLER_TARGET}
    src/controller/controller_soc_meter/ControllerSocMeter.cpp
    src/controller/Controller.cpp
    src/controller/main.cpp
)

target_include_directories(${CONTROLLER_TARGET}
    PUBLIC
    # Controller
    include/controller
    include/controller/controller_soc_meter
    # Other
    include/pin_map
    include/NRF24L01
    include/joystick
    include/adc_unit
    include/cell_soc_meter
    include/multiplexer
)

target_link_libraries(${CONTROLLER_TARGET}
    pico_stdlib
    hardware_spi
    hardware_adc

    NRF24L01
)

pico_enable_stdio_usb(${CONTROLLER_TARGET} 1)
pico_enable_stdio_uart(${CONTROLLER_TARGET} 1)

pico_add_extra_outputs(${CONTROLLER_TARGET})