#include <utility>
#include "NRF24L01Plus.hpp"

#define ADC0_GPIO 26
#define ADC1_GPIO 27

class Controller {
public:
    Controller();
    std::pair<unsigned int, unsigned int> getJoystickPosition();
    NRF24L01Plus& getTransceiver();
private:
    NRF24L01Plus transceiver_;
};