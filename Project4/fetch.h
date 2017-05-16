#ifndef FETCH_H
#define FETCH_H

#include <systemc.h>

#include "estado.h"
#include "shared.h"

#include "ibusmaster.h"


SC_MODULE(Fetch)
{
    sc_fifo_in<Estado*> stateIn;
    sc_fifo_out<Estado*> stateOut;

    sc_port<IBusMaster> memoryPort, registerPort;

    void thread();

    SC_CTOR(Fetch)
    {
        SC_THREAD(thread);
    }

private:
    Estado *_curState;
};


void Fetch::thread()
{
    for (;;) {
        std::cout << "Start Fetch Execution: " << std::endl;
        _curState = stateIn.read();

        // Read Register
        registerPort->readMasterReqEvent($pc);
        wait(registerPort->readMasterRecEvent(&_curState->pc));

        // Read Memory
        memoryPort->readMasterReqEvent(_curState->pc);
        wait(memoryPort->readMasterRecEvent(&_curState->instruction));

        stateOut.write(_curState);
    }
}

#endif // FETCH_H
