cmake_minimum_required(VERSION 3.10)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(controller C CXX ASM)

pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(TARGET controller)
add_executable(${TARGET}
    src/controller_soc_meter/ControllerSocMeter.cpp
    src/joystick/JoystickManager.cpp
    src/Controller.cpp
    src/main.cpp
)

target_include_directories(${TARGET} PUBLIC
    include
    include/controller_soc_meter
    include/joystick
)

target_link_libraries(${TARGET}
    pico_stdlib

    hardware_adc
    hardware_spi

    NRF24L01
)

pico_enable_stdio_usb(${TARGET} 1)
pico_enable_stdio_uart(${TARGET} 0)

pico_add_extra_outputs(${TARGET})