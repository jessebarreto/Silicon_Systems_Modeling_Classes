#include <systemc.h>

#ifndef ULA32_H
#define ULA32_H

SC_MODULE(Ula32)
{
    // Pins
    sc_in<int32_t> a, b;
    sc_in<int8_t> control;
    sc_out<int32_t> z;
    sc_out<bool> zero;

    void process();

    SC_CTOR(Ula32)
    {
        SC_METHOD(process);
        sensitive << a << b << control;
    }
};

void Ula32::process()
{
    int32_t result;
    switch (control) {
    case 0:
        result = a & b;
        break;
    case 1:
        result = a | b;
        break;

    case 2:
        result = a + b;
        break;
    case 6:
        result = a - b;
        break;
    case 7:
        result = (a < b);
        break;
    case 12:
        result = !(a | b);
        break;
    default:
        break;
    }
    z = result;
    zero = (result == 0);
}


#endif // ULA32_H
