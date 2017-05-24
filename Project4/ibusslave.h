#ifndef IBUSSLAVE_H
#define IBUSSLAVE_H

#include <systemc.h>


class IBusSlave : virtual public sc_interface
{
public:
    virtual bool writeSlave(uint16_t* data, unsigned address) = 0;

    virtual bool readSlave(uint16_t *data, unsigned address) = 0;

    virtual uint16_t *getSlaveDataReference() = 0;
};

#endif // IBUSSLAVE_H
