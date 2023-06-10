#include "RC_Module.hpp"


class RC_TX_Module : RC_Module
{
    public:
        RC_TX_Module();
        RC_TX_Module(spi_inst_t spi, uint csn, uint ce):RC_Module(spi_inst_t spi, uint csn, uint ce);
}