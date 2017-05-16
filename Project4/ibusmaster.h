#ifndef IBUSMASTER_H
#define IBUSMASTER_H

#include <systemc.h>


class IBusMaster : virtual public sc_interface
{
public:
    virtual sc_event& writeMasterReqEvent(unsigned address, uint16_t& newValue) = 0;

    virtual sc_event& readMasterReqEvent(unsigned address) = 0;

    virtual sc_event& readMasterRecEvent(uint16_t *data) = 0;

    virtual sc_event& writeMasterRecEvent(uint16_t *data) = 0;
};

#endif // IBUS_H
