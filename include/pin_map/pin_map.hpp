#pragma once

using GpioPin = unsigned int;

// +-------------------+
// |       Drone       |
// +-------------------+

// Engines
using EnginePosition = unsigned int;
// PIO number
// Engine pins

// State machines


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
