#include <systemc.h>

#ifndef FFD_H
#define FFD_H

SC_MODULE(FlipFlopD)
{
    sc_in<bool> d, clk;
    sc_out<bool> q, not_q;

    void process();

    SC_CTOR(FlipFlopD)
    {
        SC_METHOD(process);
        sensitive << clk.pos();
    }
};

void FlipFlopD::process()
{
    q = d;
    not_q = !d;
}

#endif // FFD_H
