#ifndef DECODE_H
#define DE

#include <systemc.h>

#include "estado.h"
#include "shared.h"

#include "ibusmaster.h"

SC_MODULE(Decode)
{
    sc_fifo_in<Estado*> stateIn;
    sc_fifo_out<Estado*> stateOut;

    void thread();

    SC_CTOR(Decode)
    {
        SC_THREAD(thread);
    }

private:
    Estado *_curState;
};

void Decode::thread()
{
    for (;;) {
        std::cout << "Start Decode Execution" << std::endl;
        _curState = stateIn.read();

        _curState->opcode = (_curState->instruction >> 12) & 0xF;
        _curState->rs = (_curState->instruction >> 8) & 0xF;
        _curState->rt = (_curState->instruction >> 4) & 0xF;
        _curState->rd = _curState->instruction & 0xF;
        _curState->k4 = (_curState->instruction & 0x8)?(0xFFF0 | _curState->rd) : _curState->rd;
        _curState->k8 = (char) (_curState->instruction & 0xFF);

        stateOut.write(_curState);
    }
}

#endif // DECODE_H
