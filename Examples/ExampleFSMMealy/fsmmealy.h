#include <systemc.h>

#ifndef FSMMEALY_H
#define FSMMEALY_H

enum t_state {
    S0, S1, S2
};

SC_MODULE(FSMMealy)
{
    sc_in<bool> clk, reset;
    sc_in<bool> in1, in2;
    sc_out<bool> out1, out2;
    sc_signal<t_state> state, next_state;

    void processState();

    void processOutput();

    void processNextState();

    SC_CTOR(FSMMealy)
    {
        SC_METHOD(processState);
        sensitive << clk.pos();

        SC_METHOD(processOutput);
        sensitive << state << in1 << in2;

        SC_METHOD(processNextState);
        sensitive << state << in1 << in2;
    }
};

void FSMMealy::processOutput()
{
    switch (state) {
    case S0:
        out1 = (in1.read() || in2.read()) ? true : false;
        out2 = false;
        break;
    case S1:
        out1 = false;
        out2 = true;
        break;
    case S2:
        out1 = false;
        out2 = false;
        break;
    default:
        out1 = false;
        out2 = false;
        break;
    }
}

void FSMMealy::processNextState()
{
    switch (state) {
    case S0:
        next_state = in1.read() ? S1 : S0;
        break;
    case S1:
        next_state = !in2.read() ? S0 : S2;
        break;
    case S2:
        next_state = in2.read() ? S0 : S2;
        break;
    default:
        next_state = S0;
        break;
    }
}

void FSMMealy::processState()
{
    if (reset.read()) {
        state = S0;
    } else {
        state = next_state;
    }
}

#endif // FSMMEALY_H
