
#include <systemc.h>

#ifndef MUX_H
#define MUX_H

SC_MODULE(Multiplexer4in8bits)
{
    sc_in<sc_uint<8> > in1, in2, in3, in4;
    sc_in<sc_uint<2> > sel;
    sc_out<sc_uint<8> > mux_out;

    void process();

    SC_CTOR(Multiplexer4in8bits)
    {
        SC_METHOD(process);
        sensitive << in1 << in2 << in3 << in4 << sel;
    }
};

void Multiplexer4in8bits::process()
{
    switch(sel.read().to_uint()) {
        case (0):
            mux_out = in1;
            break;
        case (1):
            mux_out = in2;
            break;
        case (2):
            mux_out = in3;
            break;
        case (3):
            mux_out = in4;
            break;
        default:
            mux_out = 0;
            break;
    }
}

#endif // MUX_H
