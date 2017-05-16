#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H

#include <systemc.h>

#include "ibusslave.h"
#include "shared.h"

SC_MODULE(MemoryBlock)
{
    // Channel
    sc_port<IBusSlave> busPort;

    void read();

    void write();

    SC_HAS_PROCESS(MemoryBlock);

    MemoryBlock(const sc_module_name& name, unsigned memorySize) : sc_module(name)
    {
        _memorySize = memorySize;
        _memoryData = new uint16_t(_memorySize);

        loadProgram(_memoryData);

        SC_THREAD(read);
        SC_THREAD(write);
    }

    uint16_t *getMemoryReference();

private:
    unsigned _memorySize;
    uint16_t *_memoryData;

};

uint16_t *MemoryBlock::getMemoryReference()
{
    return _memoryData;
}

void MemoryBlock::read()
{
    for (;;) {
        wait(busPort->readSlaveReqEvent());
        busPort->readSlaveRecEvent(_memoryData).notify();
    }
}

void MemoryBlock::write()
{
    for (;;) {
        wait(busPort->writeSlaveReqEvent(_memoryData));
        busPort->writeSlaveRecEvent().notify();
    }
}

#endif // MEMORYBLOCK_H
