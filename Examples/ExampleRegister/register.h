
#include <systemc.h>

#ifndef REGISTER_H
#define REGISTER_H

#define WIDTH 8

SC_MODULE(Register)
{
    sc_in<sc_uint<WIDTH> > dataIn;
    sc_in<bool> clk;
    sc_out<sc_uint<WIDTH> > dataOut;

    void process();

    SC_CTOR(Register)
    {
        SC_METHOD(process);
        sensitive << clk.pos();
    }
};

void Register::process()
{
    dataOut = dataIn;
}

#endif // REGISTER_H
