#include "ula.h"

void ula::proc()
{
    switch (opcode.read()) {
        case ADD:
            Z.write(A.read() + B.read());
            zero = ((A.read() + B.read()) == 0);
            break;
        case SUB:
            Z.write(A.read() - B.read());
            zero = ((A.read() - B.read()) == 0);
            break;
        case AND:
            Z.write(A.read() & B.read());
            zero = ((A.read() & B.read()) == 0);
            break;
        case OR:
            Z = A.read() | B.read();
            zero = ((A.read() | B.read()) == 0);
            break;
        case NOT:
            Z = ~A.read();
            zero = ((~A.read()) == 0);
            break;
        case XOR:
            Z = A.read() ^ B.read();
            zero = ((A.read() ^ B.read()) ==0);
            break;
        case BYPASS:
            Z = A.read();
            zero = ( A.read()==0);
            break;
        case SLT:
            if (A.read() < B.read()) {
                Z = 1;
                zero = false;
            } else {
                Z = 0;
                zero = true;
            }
            break;
        default:
            break;
    }
}
