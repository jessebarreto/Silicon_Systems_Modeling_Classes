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
    // Stage FIFOs
    sc_fifo<Estado*> fifoFetch, fifoDecode, fifoExecute;

    // Memory and Registers Direct Access Blocks
    MemoryBlock memory;
    RegisterBlock registers;

    // Connection Bus
    Bus bus;

    // Stages of the Processor
    Fetch fetch;
    Decode decode;
    Execute execute;

    // Constructor
    SC_CTOR(SystemReq2) :
        memory("MemoryBlock", MAX_MEM),
        registers("RegisterBlock"),
        bus("Bus"),
        fetch("FetchStage"),
        decode("DecodeStage"),
        execute("ExecuteStage")
    {
        // Start execute Fifo
        fifoExecute.write(new Estado());

        // Connect Slaves to Bus
        bus.slavePort(registers);
        bus.slavePort(memory);

        // Processor Stages
        // Fetch
        fetch.busPort(bus);
        fetch.stateIn(fifoExecute);
        fetch.stateOut(fifoFetch);
        // Decode
        decode.stateIn(fifoFetch);
        decode.stateOut(fifoDecode);
        //Execute
        execute.busPort(bus);
        execute.stateIn(fifoDecode);
        execute.stateOut(fifoExecute);
    }
};

#endif // SISTEMA2_H
