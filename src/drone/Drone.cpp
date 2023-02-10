#include "Drone.hpp"


Drone::Drone()
{
    char engine_pins[NR_OF_ENGINES] = {
        ESC_PIN_ENGINE_1,
        ESC_PIN_ENGINE_2,
        ESC_PIN_ENGINE_3,
        ESC_PIN_ENGINE_4
    };
    char engine_sm_ids[NR_OF_ENGINES] = {
        SM_ID_ENGINE_1,
        SM_ID_ENGINE_2,
        SM_ID_ENGINE_3,
        SM_ID_ENGINE_4
    };

    // Engine configuration
    for (uint i = 0; i < NR_OF_ENGINES; i++)
    {
        engines[i] = Engine(PIO, engine_sm_ids[i], engine_pins[i]);
    }
}