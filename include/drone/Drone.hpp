#include <vector>
#include "Engine.hpp"
#include "NRF24L01PlusRX.hpp"

class Drone
{
public:
    Drone();
    NRF24L01PlusRX& get_transceiver();
private:
    std::vector<Engine> engines_;
    NRF24L01PlusRX transceiver_;
};