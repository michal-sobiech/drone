#include "EngineManager.hpp"

#include <array>

#include "Engine.hpp"
#include "EngineManagerConfig.hpp"


EngineManager::EngineManager(const EngineManagerConfig& config)
{
    StateMachineNo state_machine_no = 0;
    for (auto engine_pin_pair : engines_and_pins) {
        *engine_pin_pair.first = Engine(
            config.pio,
            state_machine_no,
            engine_pin_pair.second
        );
        ++state_machine_no;
    }
}

void move(const DroneMovement& movement)
{
    
}

void set_thrust(const EngineControlSignals& signals)
{
    std::array<std::pair<>> engines_and_
}