#ifndef SISTEMA_H
#define SISTEMA_H

#include "systemc.h"
#include "ula.h"
#include "ula_tb.h"

SC_MODULE ( top )
{
    ula_tb tb;
    ula u;
    sc_signal< sc_int<SIZE> > A, B, Z;
    sc_signal< sc_uint<3> > opcode;
    sc_signal< bool > zero;

    SC_CTOR ( top ) : tb("tb"), u("u")
    {
        u.opcode(opcode); tb.opcode(opcode);
        u.A(A); tb.A(A);
        u.B(B); tb.B(B);
        u.Z(Z); tb.Z(Z);
        u.zero(zero); tb.zero(zero);
    }
};

#endif // SISTEMA_H
