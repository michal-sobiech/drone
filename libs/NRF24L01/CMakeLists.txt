cmake_minimum_required(VERSION 3.10)

project(NRF24L01)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_FILES
    src/NRF24L01.cpp
    src/NRF24L01RX.cpp
    src/NRF24L01TX.cpp
)

add_library(nrf24l01 STATIC ${SRC_FILES})

target_include_directories(nrf24l01 include)