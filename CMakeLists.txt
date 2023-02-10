cmake_minimum_required(VERSION 3.13)

# pico sdk
include(pico_sdk_import.cmake)

# run the other cmake
include($ENV{PICO_SDK_PATH}/tools/CMakeLists.txt)

project(drone C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# message(STATUS "MESSAGE:  ${CMAKE_CURRENT_LIST_DIR}")

add_executable(drone
    src/drone/main.cpp
    src/drone/Drone.cpp
    src/drone/Engine.cpp
    src/drone/Drone.hpp
    src/drone/Engine.hpp
    src/drone/dshot.pio
)

target_link_libraries(drone
    pico_stdlib
    hardware_pio
)

add_executable(controller
    src/controller/main.cpp
)

target_link_libraries(controller
    pico_stdlib
)

pico_generate_pio_header(${PROJECT_NAME}  
    ${CMAKE_CURRENT_LIST_DIR}/src/drone/dshot.pio
)

pico_enable_stdio_usb(drone 1)
pico_enable_stdio_uart(drone 1)

pico_add_extra_outputs(drone)

