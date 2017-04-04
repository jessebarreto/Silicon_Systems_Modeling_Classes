#include "ula_tb.h"

void ula_tb::aciona()
{
    std::cout << "---" << "   OPCODE " << " A " << "B " << "Z " << " zero" << std::endl;
    for(uint i = 0; i < 8; i++) {
        opcode = i;
        A = 7;
        B = 6;
        wait(1, SC_PS);
        std::cout << sc_time_stamp() << " " << opcode << " " << A << " " << B << " " << Z << " " << zero << std::endl;

        A = 8;
        B = 10;
        wait(1, SC_PS);
        std::cout << sc_time_stamp() << " " << opcode << " " << A << " " << B << " " << Z << " " << zero << std::endl;

        A = 2;
        B = 2;
        wait(1, SC_PS);
        std::cout << sc_time_stamp() << " " << opcode << " " << A << " " << B << " " << Z << " " << zero << std::endl;

        A = 0;
        B = 0;
        wait(1, SC_PS);
        std::cout << sc_time_stamp() << " " << opcode << " " << A << " " << B << " " << Z << " " << zero << std::endl;
    }
    wait(1, SC_PS);
    std::cout << sc_time_stamp() << " " << opcode << " " << A << " " << B << " " << Z << " " << zero << std::endl;
}
