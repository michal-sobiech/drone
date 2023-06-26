cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(drone C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# The main module
file(GLOB_RECURSE PROJECT_SRC_FILES src/drone/*.cpp)
add_executable(${PROJECT_NAME}
    ${PROJECT_SRC_FILES}  
    # src/drone/Drone.cpp
    # src/drone/engine/Engine.cpp
    src/main.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    include/drone
    include/drone/engine
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_pio
    hardware_spi
)

pico_generate_pio_header(${PROJECT_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/drone/dshot.pio
)

# NRF24L01+
set(NRF24L01_plus_TARGET NRF24L01_plus)
file(GLOB_RECURSE NRF24L01_plus_SRC_FILES src/NRF24L01_plus/*.cpp)
add_library(${NRF24L01_plus_TARGET}
    ${NRF24L01_plus_SRC_FILES}
    # src/NRF24L01_plus/RC_Module.cpp
)
target_include_directories(${NRF24L01_plus_TARGET}
    PRIVATE
    include/NRF24L01_plus
)
target_link_libraries(${NRF24L01_plus_TARGET} 
    pico_stdlib
    hardware_spi
)

# Controller
set(CONTROLLER_TARGET controller)
file(GLOB_RECURSE CONTROLLER_SRC_FILES src/controller/*.cpp)
add_executable(${CONTROLLER_TARGET}
    ${CONTROLLER_SRC_FILES}
)
target_include_directories(${CONTROLLER_TARGET}
    PUBLIC
    include/controller
)
target_link_libraries(${CONTROLLER_TARGET}
    pico_stdlib
    hardware_pio
    hardware_spi
)

pico_enable_stdio_usb(drone 1)
pico_enable_stdio_uart(drone 1)

pico_add_extra_outputs(drone)

