#ifndef REGISTERBLOCK_H
#define REGISTERBLOCK_H

#include <systemc.h>

#include "shared.h"

#include "ibusslave.h"

SC_MODULE(RegisterBlock)
{
    sc_port<IBusSlave> busPort;

    void read();

    void write();

    SC_CTOR(RegisterBlock)
    {
        _regBank[$pc] = 0;
        _regBank[$zero] = 0;

        SC_THREAD(read);

        SC_THREAD(write);
    }

private:
    uint16_t _regBank[16];
};

void RegisterBlock::read()
{
    for (;;) {
        wait(busPort->readSlaveReqEvent());
        busPort->readSlaveRecEvent(_regBank);
    }
}

void RegisterBlock::write()
{
    for (;;) {
        wait(busPort->writeSlaveReqEvent(_regBank));
        busPort->writeSlaveRecEvent().notify();
    }
}

#endif // REGISTERBLOCK_H
