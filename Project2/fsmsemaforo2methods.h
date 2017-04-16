#include <systemc.h>

#include "fsmsemaforo3methods.h"

#ifndef FSMSEMAFORO2METHODS_H
#define FSMSEMAFORO2METHODS_H


SC_MODULE(FSMSemaforo2Methods)
{
    sc_in<bool> clk, reset;
    sc_in<bool> sensorNorth, sensorSouth;
    sc_in<bool> il, ic;

    sc_out<bool> at;
    sc_out<sc_uint<3> > AE;
    sc_out<sc_uint<3> > VL;

    sc_signal<TState> state, nextState;

    SC_CTOR(FSMSemaforo2Methods)
    {
        SC_METHOD(_processState);
        sensitive << clk.pos() << reset;

        SC_METHOD(_processOutputNextState);
        sensitive << reset << state
                  << il << ic
                  << sensorNorth << sensorSouth;
    }

private:
    void _processState();

    void _processOutputNextState();
};
#endif // FSMSEMAFORO2METHODS_H
