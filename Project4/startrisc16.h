#ifndef STARTRISC16_H
#define STARTRISC16_H

#include <systemc.h>

#include "estado.h"

SC_MODULE(Start)
{
    sc_fifo_out<Estado*> stateOut;

    SC_CTOR(Start)
    {
        SC_THREAD(start);
    }

private:
    void start();

    Estado *begin;
};

void Start::start()
{
    std::cout << "Start RISC16 Processor." << std::endl;

    begin = new Estado();
    stateOut.write(begin);
}

#endif // STARTRISC16_H
