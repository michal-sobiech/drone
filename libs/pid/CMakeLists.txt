cmake_minimum_required(VERSION 3.10)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pid)

pico_sdk_init()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_FILES
    src/PID.cpp
)

set(TARGET pid)
add_library(${TARGET} STATIC ${SRC_FILES})

target_include_directories(${TARGET} PUBLIC include)