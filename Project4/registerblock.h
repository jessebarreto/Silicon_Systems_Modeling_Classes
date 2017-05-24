#ifndef REGISTERBLOCK_H
#define REGISTERBLOCK_H

#include <systemc.h>

#include "shared.h"
#include "ibusslave.h"

class RegisterBlock : public sc_module, public IBusSlave
{
public:
    SC_HAS_PROCESS(RegisterBlock);
    RegisterBlock(const sc_module_name &name) : sc_module(name)
    {
        _regBank[$pc] = 0;
        _regBank[$zero] = 0;
    }

    bool writeSlave(uint16_t* data, unsigned address);

    bool readSlave(uint16_t *data, unsigned address);

    uint16_t *getSlaveDataReference();

private:
    uint16_t _regBank[NUMBEROFREGISTERS];
};



#endif // REGISTERBLOCK_H

bool RegisterBlock::writeSlave(uint16_t *data, unsigned address)
{
    if (address < 0 || address > NUMBEROFREGISTERS) {
        std::cout << "[Critical Error] Register doesn't not exist" << std::endl;
        return false;
    }

    // Make Sure $zero is ALWAYS zero!!!
    if (address != $zero) {
        _regBank[address] = *data;
    }

    return true;
}

bool RegisterBlock::readSlave(uint16_t *data, unsigned address)
{
    if (address < 0 || address > NUMBEROFREGISTERS) {
        std::cout << "[Critical Error] Register doesn't not exist" << std::endl;
        return false;
    }

    *data = _regBank[address];
    return true;
}

uint16_t *RegisterBlock::getSlaveDataReference()
{
    return _regBank;
}
