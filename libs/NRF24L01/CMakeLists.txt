cmake_minimum_required(VERSION 3.10)

include(pico_sdk_import.cmake)

project(NRF24L01)

pico_sdk_init()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_FILES
    src/NRF24L01.cpp
    src/NRF24L01RX.cpp
    src/NRF24L01TX.cpp
)

set(TARGET nrf24l01)
add_library(${TARGET} STATIC ${SRC_FILES})

target_include_directories(${TARGET} PUBLIC include)

target_link_libraries(${TARGET}
    pico_stdlib

    hardware_spi
)