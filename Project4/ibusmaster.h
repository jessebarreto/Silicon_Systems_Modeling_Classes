#ifndef IBUSMASTER_H
#define IBUSMASTER_H

#include <systemc.h>


class IBusMaster : virtual public sc_interface
{
public:
    virtual bool writeMaster(uint16_t *data, unsigned address, unsigned slaveId) = 0;

    virtual bool readMaster(uint16_t *data, unsigned address, unsigned slaveId) = 0;

    virtual uint16_t *getSlaveReference(unsigned slaveId) = 0;
};

#endif // IBUS_H
