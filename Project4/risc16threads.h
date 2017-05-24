#ifndef RISC16THREADS_H
#define RISC16THREADS_H

#include <systemc.h>

#include "shared.h"

SC_MODULE(Risc16Threads)
{
    void start();

    void fetch();

    void decode();

    void execute();

    SC_HAS_PROCESS(Risc16Threads);

    Risc16Threads(const sc_module_name& name, unsigned memorySize) :
        sc_module(name),
        _memorySize(memorySize),
        _memoryData(new uint16_t(_memorySize))

    {
        _memorySize = memorySize;
        _memoryData = new uint16_t [_memorySize];
        _regBank[$zero] = 0; // Register 0
        _regBank[$pc] = 0; // Program Counter

        SC_THREAD(start);

        SC_THREAD(fetch);

        SC_THREAD(decode);

        SC_THREAD(execute);
    }

    uint16_t *getMemoryReference()
    {
        return _memoryData;
    }

private:
    // Memory
    unsigned _memorySize;
    uint16_t *_memoryData;

    // Registers
    uint16_t _regBank[16];
    uint16_t _instReg;

    // Program Counter and "Program Wires"
    uint8_t opcode, rs, rt, rd, k4, k8;

    // Events
    sc_event _eventFetch, _eventDecode, _eventExecute;
};

void Risc16Threads::start()
{
    _eventFetch.notify(SC_ZERO_TIME);
    std::cout << "Start Risc Execution: " << std::endl;
}

void Risc16Threads::fetch()
{
    for (;;) {
        wait(_eventFetch);

        _instReg = _memoryData[_regBank[$pc]];
        _regBank[$pc]++;
#if DEBUG
        if (_regBank[$pc] == 0xFF) { // HALT STATE
            std::cout << "End Risc Execution: " << std::endl;
            std::cout << "Registers: " << std::endl;
            dump_breg(_regBank);
            std::cout << "Memory: " << std::endl;
            dump_mem(_memoryData, 0, 60, 'H');
            break;
        }
#endif
        _eventDecode.notify(SC_ZERO_TIME);
    }
}

void Risc16Threads::decode()
{
    for (;;) {
        wait(_eventDecode);

        opcode = (_instReg >> 12) & 0xF;
        rs = (_instReg >> 8) & 0xF;
        rt = (_instReg >> 4) & 0xF;
        rd = _instReg & 0xF;
        k4 = (_instReg & 0x8)?(0xFFF0 | rd) : rd;
        k8 = (char) (_instReg & 0xFF);

        _eventExecute.notify(SC_ZERO_TIME);
    }
}

void Risc16Threads::execute()
{
    for (;;) {
        wait(_eventExecute);

        std::cout << "Execute Risc Execution: pc - " << _regBank[$pc]
                  << " | op: " << opcode
                  <<  std::endl;


        switch (opcode) {
                case i_ADD:   _regBank[rd] = _regBank[rs] + _regBank[rt]; break;
                case i_SUB:   _regBank[rd] = _regBank[rs] - _regBank[rt]; break;
                case i_AND:   _regBank[rd] = _regBank[rs] & _regBank[rt]; break;
                case i_OR :   _regBank[rd] = _regBank[rs] | _regBank[rt]; break;
                case i_XOR:   _regBank[rd] = _regBank[rs] ^ _regBank[rt]; break;
                case i_NOT:   _regBank[rs] = ~_regBank[rt]; break;
                //case i_NOT:   _regBank[rd] = ~_regBank[rs]; break;
                case i_ADDi:  _regBank[rs] = _regBank[rs] + k8; break;
                case i_SHIFT:
                    if (k8 < 0) _regBank[rs] = _regBank[rs] << (-k8);
                    else _regBank[rs] = _regBank[rs] >> k8;
                    break;
                case i_SLT:  _regBank[rd] = _regBank[rs] < _regBank[rt]; break;
                case i_LW:   _regBank[rd] = _memoryData[_regBank[rs] + _regBank[rt]]; break;
                case i_SW:   _memoryData[_regBank[rs] + _regBank[rt]] = _regBank[rd]; break;
                case i_LUI:  _regBank[rs] = k8 << 8; break;
                case i_BEQ:	 if (_regBank[rs] == _regBank[rt]) _regBank[$pc] = _regBank[$pc] + k4; break;
                case i_BNE:	 if (_regBank[rs] != _regBank[rt]) _regBank[$pc] = _regBank[$pc] + k4; break;
                case i_J:	 _regBank[$pc] = _regBank[rs] + k8; break;
                case i_JAL:	 _regBank[$ra] = _regBank[$pc];
                    _regBank[$pc] = _regBank[rs] + k8;
                    break;
                default:
                    break;
            }
            _regBank[$zero] = 0; // Makes sure $zero is zero, ALWAYS


        _eventFetch.notify(SC_ZERO_TIME);
    }
}

#endif // RISC16THREADS_H
