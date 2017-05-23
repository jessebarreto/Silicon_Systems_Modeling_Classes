#include <systemc.h>

#include "startrisc16.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include "memoryblock.h"
#include "registerblock.h"
#include "estado.h"

#include "bus.h"

#include "shared.h"

#ifndef SISTEMA2_H
#define SISTEMA2_H

SC_MODULE(SystemReq2)
{
    Bus memoryBus, registersBus;

    sc_fifo<Estado*> fifoFetch, fifoDecode, fifoExecute;

    MemoryBlock memory;
    RegisterBlock registers;

    Fetch fetch;
    Decode decode;
    Execute execute;

    SC_CTOR(SystemReq2) :
        memory("MemoryBlock", MAX_MEM),
        registers("Registerblock"),
        memoryBus("MemoryBus"),
        registersBus("RegistersBus"),
        fetch("FetchStage"),
        decode("DecodeStage"),
        execute("ExecuteStage")
    {
        // Memory and Register Block
        memory.busPort(memoryBus);
        registers.busPort(registersBus);

        // Start
        fifoExecute.write(new Estado());

        // Processor Stages
        // Fetch
        fetch.memoryPort(memoryBus);
        fetch.registerPort(registersBus);
        fetch.stateIn(fifoExecute);
        fetch.stateOut(fifoFetch);
        // Decode
        decode.stateIn(fifoFetch);
        decode.stateOut(fifoDecode);
        //Execute
        execute.memoryPort(memoryBus);
        execute.registerPort(registersBus);
        execute.stateIn(fifoDecode);
        execute.stateOut(fifoExecute);
    }
};

#endif // SISTEMA2_H
