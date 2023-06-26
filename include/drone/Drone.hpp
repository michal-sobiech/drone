#include "Engine.hpp"

#define NR_OF_ENGINES 4     // 3 or 4
#define _CONCAT(a, b) a##b
#define CONCAT(a, b) _CONCAT(a, b)
#define ESC_PIN_ENGINE_1 0
#define ESC_PIN_ENGINE_2 15
#define ESC_PIN_ENGINE_3 16
#define ESC_PIN_ENGINE_4 28
#define SM_ID_ENGINE_1 0
#define SM_ID_ENGINE_2 1
#define SM_ID_ENGINE_3 2
#define SM_ID_ENGINE_4 3
#define PIO pio0

#if (NR_OF_ENGINES != 3 && NR_OF_ENGINES != 4)
#error "Wrong number of engines"
#endif

class Drone
{
    public:
        Drone();
    private:
        char engine_pins_[NR_OF_ENGINES];
        char engine_sm_ids_[NR_OF_ENGINES];
        Engine engines_[NR_OF_ENGINES];
};