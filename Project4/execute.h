#ifndef EXECUTE_H
#define EXECUTE_H

#include <systemc.h>

#include "estado.h"
#include "shared.h"

#include "ibusmaster.h"

SC_MODULE(Execute)
{
    sc_fifo_in<Estado*> stateIn;
    sc_fifo_out<Estado*> stateOut;

    sc_port<IBusMaster> memoryPort, registerPort;

    void thread();

    SC_CTOR(Execute)
    {
        SC_THREAD(thread);
    }
private:
    Estado *_curState;
};

void Execute::thread()
{
    for (;;) {
        std::cout << "Execute Risc Execution: " <<  std::endl;
        _curState = stateIn.read();


        stateOut.write(_curState);
    }
}

#endif // EXECUTE_H
