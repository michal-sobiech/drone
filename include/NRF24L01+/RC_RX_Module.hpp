#include "RC_Module.hpp"


class RC_RX_Module : RC_Module
{
    public:
        RC_RX_Module():RC_RX_Module();
        RC_RX_Module(spi_inst_t spi, uint csn, uint ce):RC_Module(spi_inst_t spi, uint csn, uint ce);
}