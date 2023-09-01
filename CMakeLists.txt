cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(drone C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# +---------------------+
# |    Common files     |
# +---------------------+

set(NRF24L01_plus_SRC_FILES 
    src/NRF24L01_plus/NRF24L01.cpp
    src/NRF24L01_plus/NRF24L01RX.cpp
    src/NRF24L01_plus/NRF24L01TX.cpp)
set(MPU6050_SRC_FILES 
    src/MPU6050/MPU6050.cpp)

# +---------------------+
# |        Drone        |
# +---------------------+
set(DRONE_TARGET drone)
add_executable(${DRONE_TARGET}
    # Drone
    src/drone/Drone.cpp
    src/drone/main.cpp
    src/drone/drone_soc_meter/DroneSocMeter.cpp
    src/drone/engine/Engine.cpp
    # Other
    ${NRF24L01_plus_SRC_FILES}
    ${MPU6050_SRC_FILES}
)

target_include_directories(${DRONE_TARGET}
    PUBLIC
    include/drone
    include/drone_soc_meter
    include/drone/engine
    include/NRF24L01_plus
    include/MPU6050
)

target_link_libraries(${DRONE_TARGET}
    pico_stdlib
    hardware_pio
    hardware_spi
    hardware_adc
    hardware_i2c
)

pico_generate_pio_header(${DRONE_TARGET}
    ${CMAKE_CURRENT_LIST_DIR}/src/drone/dshot.pio
)

pico_enable_stdio_usb(${DRONE_TARGET} 1)
pico_enable_stdio_uart(${DRONE_TARGET} 1)

pico_add_extra_outputs(${DRONE_TARGET})

# +---------------------+
# |     Controller      |
# +---------------------+
set(CONTROLLER_TARGET controller)
add_executable(${CONTROLLER_TARGET}
    # Controller files
    src/controller/controller_soc_meter/ControllerSocMeter.cpp
    src/controller/Controller.cpp
    src/controller/main.cpp
    # Other
    ${NRF24L01_plus_SRC_FILES}
    src/joystick/JoystickManager.cpp
    src/adc_unit/AdcUnit.cpp
)
target_include_directories(${CONTROLLER_TARGET}
    PUBLIC
    # Controller
    include/controller
    include/controller/controller_soc_meter
    # Other
    include/NRF24L01_plus
    include/joystick
    include/adc_unit
)
target_link_libraries(${CONTROLLER_TARGET}
    pico_stdlib
    hardware_spi
    hardware_adc
)

pico_enable_stdio_usb(${CONTROLLER_TARGET} 1)
pico_enable_stdio_uart(${CONTROLLER_TARGET} 1)

pico_add_extra_outputs(${CONTROLLER_TARGET})