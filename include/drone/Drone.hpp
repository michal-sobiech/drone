#include <vector>
#include "Engine.hpp"
#include "NRF24L01Plus.hpp"

class Drone
{
public:
    Drone();
    NRF24L01Plus& get_transceiver();
private:
    std::vector<Engine> engines_;
    NRF24L01Plus transceiver_;
};