#ifndef ULA_H
#define ULA_H

#include "systemc.h"

enum OPCODE {ADD, SUB, AND, OR, NOT, XOR, BYPASS, SLT};

#define SIZE 16

SC_MODULE(ula) {

    sc_in< sc_uint<3> > opcode;
    sc_in< sc_int<SIZE> > A, B;
    sc_out< sc_int<SIZE> > Z;
    sc_out<bool> zero;

    void proc(void);

    SC_CTOR(ula)
    {
        SC_METHOD(proc);
        sensitive << A << B << opcode;
    }
};

#endif // ULA_H
