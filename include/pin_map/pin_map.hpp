#pragma once

using GpioPin = unsigned int;

// +-------------------+
// |       Drone       |
// +-------------------+

// SoC meter and its mux
#define DRONE_SOC_METER_GPIO_NO 26
#define DRONE_SOC_METER_ADC_NO 0
#define DRONE_SOC_METER_MUX_SEL_H_GPIO_NO 21
#define DRONE_SOC_METER_MUX_SEL_L_GPIO_NO 20

// Engines
using EnginePosition = unsigned int;
#define FRONT_RIGHT_ENG_NO 0
#define FRONT_LEFT_ENG_NO 1
#define BACK_LEFT_ENG_NO 2
#define BACK_RIGHT_ENG_NO 3
// PIO number
#define ENG_PIO_NO 0
// Engine pins
#define FRONT_RIGHT_ENG_PIN 0
#define FRONT_LEFT_ENG_PIN 15
#define BACK_LEFT_ENG_PIN 16
#define BACK_RIGHT_ENG_PIN 28
// State machines
#define FRONT_RIGHT_ENG_SM 0
#define FRONT_LEFT_ENG_SM 1
#define BACK_LEFT_ENG_SM 2
#define BACK_RIGHT_ENG_SM 3

// +-------------------+
// |    Controller     |
// +-------------------+

// Joysticks and their mux
#define JOYSTICK_GPIO_NO 26
#define JOYSTICK_ADC_NO 0
#define JOYSTICK_MUX_SEL_H_GPIO_NO 21
#define JOYSTICK_MUX_SEL_L_GPIO_NO 20

// SoC meter
#define CONTROLLER_SOC_METER_GPIO_NO 27
#define CONTROLLER_SOC_METER_ADC_NO 1
