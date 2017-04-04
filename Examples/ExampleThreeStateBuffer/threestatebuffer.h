
#include <systemc.h>

#ifndef THREESTATEBUFFER_H
#define THREESTATEBUFFER_H

SC_MODULE(ThreeStateBuffer)
{
    sc_in<bool> enable;
    sc_in<sc_logic> inBuffer;
    sc_out<sc_logic> outBuffer;

    void process();

    SC_CTOR(ThreeStateBuffer)
    {
        SC_METHOD(process);
        sensitive << enable << inBuffer;
    }
};

void ThreeStateBuffer::process()
{
    if (enable.read()) {
        outBuffer = inBuffer;
    } else {
        outBuffer = sc_logic_Z;
    }
}

#endif // THREESTATEBUFFER_H
