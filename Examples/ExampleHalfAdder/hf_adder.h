
#include <systemc.h>

SC_MODULE(HalfAdder)
{
    sc_in<bool> x, y;
    sc_out<bool> sum, carry_out;

    void process()
    {
        sum = x ^ y;
        carry_out = x & y;
    }

    SC_CTOR(HalfAdder)
    {
        SC_METHOD(process);
        sensitive << x << y;
    }
};
