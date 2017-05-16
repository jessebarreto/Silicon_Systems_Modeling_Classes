#ifndef IBUSSLAVE_H
#define IBUSSLAVE_H

#include <systemc.h>


class IBusSlave : virtual public sc_interface
{
public:
    virtual sc_event& writeSlaveReqEvent(uint16_t* data) = 0;

    virtual sc_event& readSlaveReqEvent() = 0;

    virtual sc_event& writeSlaveRecEvent() = 0;

    virtual sc_event& readSlaveRecEvent(uint16_t *data) = 0;
};

#endif // IBUSSLAVE_H
