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

    sc_port<IBusMaster> busPort;

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

        std::cout << "Execute Risc Execution: pc - " << static_cast<int>(_curState->pc)
                  << " | op: " << static_cast<int>(_curState->opcode)
                  <<  std::endl;

        uint16_t regD, regS, regT;

        // Read Register Values
        busPort->readMaster(&regS, _curState->rs, 0);
        busPort->readMaster(&regT, _curState->rt, 0);
        busPort->readMaster(&regD, _curState->rd, 0);

        switch (_curState->opcode) {
                case i_ADD:
                    regD = regS + regT;
                    busPort->writeMaster(&regD, _curState->rd, 0);
                    break;
                case i_SUB:
                    regD = regS - regT;
                    busPort->writeMaster(&regD, _curState->rd, 0);
                    break;
                case i_AND:
                    regD = regS & regT;
                    busPort->writeMaster(&regD, _curState->rd, 0);
                    break;
                case i_OR :
                    regD = regS | regT;
                    busPort->writeMaster(&regD, _curState->rd, 0);
                    break;
                case i_XOR:
                    regD = regS ^ regT;
                    busPort->writeMaster(&regD, _curState->rd, 0);
                    break;
                case i_NOT:
                    regS = ~regT;
                    busPort->writeMaster(&regS, _curState->rs, 0);
                    break;
                //case i_NOT:   _regBank[rd] = ~_regBank[rs]; break;
                case i_ADDi:
                    regS += _curState->k8;
                    busPort->writeMaster(&regS, _curState->rs, 0);
                    break;
                case i_SHIFT:
                    if (_curState->k8 < 0) {
                        regS = regS << (-_curState->k8);
                    } else {
                        regS = regS >> _curState->k8;
                    }
                    busPort->writeMaster(&regS, _curState->rs, 0);
                    break;
                case i_SLT:
                    regD = regS < regT;
                    busPort->writeMaster(&regD, _curState->rd, 0);
                    break;
                case i_LW:
                    uint16_t memValue;
                    regD = busPort->readMaster(&memValue, regS + regT, 1);
                    busPort->writeMaster(&regD, _curState->rd, 0);
                    break;
                case i_SW:
                    busPort->writeMaster(&regD, regS + regT, 1);
                    break;
                case i_LUI:
                    regS = _curState->k8 << 8;
                    busPort->writeMaster(&regS, _curState->rs, 0);
                    break;
                case i_BEQ:
                    if (regS == regT) {
                        _curState->pc += _curState->k4;
                        busPort->writeMaster(&_curState->pc, $pc, 0);
                    }
                    break;
                case i_BNE:
                    if (regS != regT) {
                        _curState->pc += _curState->k4;
                        busPort->writeMaster(&_curState->pc, $pc, 0);
                    }
                    break;
                case i_J:
                    _curState->pc += _curState->k8;
                    busPort->writeMaster(&_curState->pc, $pc, 0);
                    break;
                case i_JAL:
                    busPort->writeMaster(&_curState->pc, $ra, 0);
                    _curState->pc = regS + _curState->k8;
                    busPort->writeMaster(&_curState->pc, $pc, 0);
                    break;
                default:
                    break;
            }
        // Make sure $zero is always zero!!! ALWAYS!!!


        stateOut.write(_curState);
    }
}

#endif // EXECUTE_H
