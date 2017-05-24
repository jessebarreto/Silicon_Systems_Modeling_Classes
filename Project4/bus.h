#ifndef BUS_H
#define BUS_H

#include <systemc.h>

#include "ibusmaster.h"
#include "ibusslave.h"

class Bus : public sc_module, public IBusMaster
{
    void run();

public:
    sc_port<IBusSlave, 0> slavePort;

    SC_HAS_PROCESS(Bus);
    Bus(const sc_module_name &name) : sc_module(name)
    {

    }

    bool writeMaster(uint16_t *data, unsigned address, unsigned slaveId);

    bool readMaster(uint16_t *data, unsigned address, unsigned slaveId);

    uint16_t *getSlaveReference(unsigned slaveId);
};

bool Bus::writeMaster(uint16_t *data, unsigned address, unsigned slaveId)
{
    if (slavePort.size() < slaveId) {
        std::cout << "[Critical Error] Wrong slave Id number" << std::endl;
        return false;
    }
    return slavePort[slaveId]->writeSlave(data, address);
}

bool Bus::readMaster(uint16_t *data, unsigned address, unsigned slaveId)
{
    if (slavePort.size() < slaveId) {
        std::cout << "[Critical Error] Wrong slave Id number" << std::endl;
        return false;
    }
    return slavePort[slaveId]->readSlave(data, address);
}

uint16_t *Bus::getSlaveReference(unsigned slaveId)
{
    if (slavePort.size() < slaveId) {
        std::cout << "[Critical Error] Wrong slave Id number" << std::endl;
        return NULL;
    }

    return slavePort[slaveId]->getSlaveDataReference();
}



#endif // BUS_H
