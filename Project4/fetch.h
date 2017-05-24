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

    sc_port<IBusMaster> busPort;

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

        // Get the State
        _curState = stateIn->read();

        // PC value
        busPort->readMaster(&_curState->pc, $pc, 0);

        // Instruction value from memory
        busPort->readMaster(&_curState->instruction, _curState->pc, 1);

        // Increment PC value
        _curState->pc++;
        busPort->writeMaster(&_curState->pc, $pc, 0);

#if DEBUG
        if (_curState->pc == 0xFF) { // HALT STATE
            std::cout << "End Risc Execution: " << std::endl;
            std::cout << "Registers: " << std::endl;
            dump_breg(busPort->getSlaveReference(0));
            std::cout << "Memory: " << std::endl;
            dump_mem(busPort->getSlaveReference(1), 0, 60, 'H');
            break;
        }
#endif

        // Send State to next stage
        stateOut->write(_curState);
    }
}

#endif // FETCH_H
