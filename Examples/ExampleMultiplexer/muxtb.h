
#include <systemc.h>

#ifndef MUXTB_H
#define MUXTB_H

SC_MODULE(Multiplexer4in8bitsTb)
{
    sc_out<sc_uint<8> > in1, in2, in3, in4;
    sc_out<sc_uint<2> > sel;
    sc_in<sc_uint<8> > mux_out;

    void acionador();

    SC_CTOR(Multiplexer4in8bitsTb)
    {
        SC_THREAD(acionador);
    }
};

void Multiplexer4in8bitsTb::acionador()
{
    in1 = 1; in2 = 3; in3 = 7; in4 = 16;
    std::cout << "-----" << "\tin1" << "\tin2" << "\tin3" << "\tin4" << "\tsel" << "\tOUT" << std::endl;

    sel = 0;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << in1 << "\t" << in2 << "\t" << in3 << "\t"
              << in4 << "\t" << sel << "\t" << mux_out << std::endl;

    sel = 1;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << in1 << "\t" << in2 << "\t" << in3 << "\t"
              << in4 << "\t" << sel << "\t" << mux_out << std::endl;

    sel = 2;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << in1 << "\t" << in2 << "\t" << in3 << "\t"
              << in4 << "\t" << sel << "\t" << mux_out << std::endl;

    sel = 3;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << in1 << "\t" << in2 << "\t" << in3 << "\t"
              << in4 << "\t" << sel << "\t" << mux_out << std::endl;

    sel = 4;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << in1 << "\t" << in2 << "\t" << in3 << "\t"
              << in4 << "\t" << sel << "\t" << mux_out << std::endl;
}

#endif // MUXTB_H
