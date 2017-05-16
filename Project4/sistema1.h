#ifndef SISTEMA1_H
#define SISTEMA1_H

#include <systemc.h>

#include "shared.h"
#include "risc16threads.h"

SC_MODULE(SystemReq1)
{
    Risc16Threads risc16;

    SC_CTOR(SystemReq1) :
        risc16("RISC16THREADS", MAX_MEM)
    {
        loadProgram(risc16.getMemoryReference());
    }

};

#endif // SISTEMA1_H
