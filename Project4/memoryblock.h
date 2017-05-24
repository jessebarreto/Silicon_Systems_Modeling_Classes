#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H

#include <systemc.h>

#include "ibusslave.h"
#include "shared.h"

class MemoryBlock : public sc_module, public IBusSlave
{
public:

    bool writeSlave(uint16_t* data, unsigned address);

    bool readSlave(uint16_t *data, unsigned address);

    uint16_t *getSlaveDataReference();

    SC_HAS_PROCESS(MemoryBlock);
    MemoryBlock(const sc_module_name& name, unsigned memorySize) : sc_module(name)
    {
        _memorySize = memorySize;
        _memoryData = new uint16_t [_memorySize];
        for (int i = 0; i < _memorySize; i++) {
            _memoryData[i] = 0;
        }

        loadProgram(_memoryData);
    }

    ~MemoryBlock()
    {
        if (_memoryData) {
            delete [] _memoryData;
            _memoryData = NULL;
        }
    }

    uint16_t *getMemoryReference();

private:
    unsigned _memorySize;
    uint16_t *_memoryData;
};

bool MemoryBlock::writeSlave(uint16_t *data, unsigned address)
{
    if (address >= _memorySize || address < 0) {
        std::cout << "[Critical Error] Segmentation Fault" << std::endl;
        return false;
    }

    _memoryData[address] = *data;
    return true;
}

bool MemoryBlock::readSlave(uint16_t *data, unsigned address)
{
    if (address >= _memorySize || address < 0) {
        std::cout << "[Critical Error] Segmentation Fault" << std::endl;
        return false;
    }

    *data = _memoryData[address];
    return true;
}

uint16_t *MemoryBlock::getSlaveDataReference()
{
    return _memoryData;
}

uint16_t *MemoryBlock::getMemoryReference()
{
    return _memoryData;
}

#endif // MEMORYBLOCK_H
