#include "DroneMovement.hpp"
#include "Engine.hpp"
#include "EngineControlSignals.hpp"
#include "PID.hpp"
#include "StaticCheckedArray.cpp"


class EngineManager {
public:
    EngineManager(const EngineManagerConfig& config);
    void move(const DroneMovement& movement);
private:
    StaticCheckedArray<Engine, 4> engines_;

    PID roll_pid_;
    PID pitch_pid_;

    void set_thrust(cont EngineControlSignals& signals);
};
