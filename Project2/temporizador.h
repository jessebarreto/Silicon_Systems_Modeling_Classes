
#include <systemc.h>

#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

#define SHORT_DURATION 3
#define LONG_DURATION 5

SC_MODULE(Temporizador)
{
    // PINS
    sc_in<bool> clk, enable;
    sc_out<bool> ic, il;

    SC_CTOR(Temporizador)
    {
        SC_METHOD(_process);
        sensitive << clk.pos() << enable;
    }

private:
    unsigned int _counter;

    void _process();
};

#endif // TEMPORIZADOR_H
