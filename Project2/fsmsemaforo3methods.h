#include <systemc.h>

#ifndef FSMSEMAFORO3METHODS_H
#define FSMSEMAFORO3METHODS_H

enum TState {
    Idle = 0,
    AEGreenGo,
    AEYellow,
    AEYellowGo,
    VLGreen,
    VLGreenGo,
    VLYellow,
    VLYellowGo
};

enum TColor {
    Red = 1,
    Yellow = 2,
    Green = 4
};

SC_MODULE(FSMSemaforo3Methods)
{
    sc_in<bool> clk, reset;
    sc_in<bool> sensorNorth, sensorSouth;
    sc_in<bool> il, ic;

    sc_out<bool> at;
    sc_out<sc_uint<3> > AE;
    sc_out<sc_uint<3> > VL;

    sc_signal<TState> state, nextState;

    SC_CTOR(FSMSemaforo3Methods)
    {
        SC_METHOD(_processState);
        sensitive << clk.pos() << reset;

        SC_METHOD(_processNextState);
        sensitive << reset << state
                  << il << ic
                  << sensorNorth << sensorSouth;

        SC_METHOD(_processOutput);
        sensitive << reset << state
                  << il << ic
                  << sensorNorth << sensorSouth;
    }

private:
    void _processState();

    void _processOutput();

    void _processNextState();
};

#endif // FSMSEMAFORO3METHODS_H
