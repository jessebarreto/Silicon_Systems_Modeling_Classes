#include <systemc.h>

#ifndef THREESTATEBUSREGENABLE_H
#define THREESTATEBUSREGENABLE_H

#define BUSSIZE 8

SC_MODULE(ThreeStateBusRegEnable)
{
    sc_in<bool> enable, clk;
    sc_in<sc_lv<BUSSIZE> > dataIn;
    sc_out<sc_lv<BUSSIZE> > dataOut;

    void process();

    void flipflop();

    SC_CTOR(ThreeStateBusRegEnable)
    {
        SC_METHOD(process);
        sensitive << enable << registered;

        SC_METHOD(flipflop);
        sensitive << clk.pos();
    }

    sc_lv<BUSSIZE> _fillBits(sc_dt::sc_logic value);
private:
    sc_signal<sc_lv<BUSSIZE> > registered;
};

sc_lv<BUSSIZE> ThreeStateBusRegEnable::_fillBits(sc_logic value)
{
    sc_lv<BUSSIZE> filled;
    for (int i = 0; i < BUSSIZE; i++) {
        filled[i] = value;
    }
    return filled;
}

void ThreeStateBusRegEnable::process()
{
    if (enable.read()) {
        dataOut = registered;
    } else {
        dataOut = _fillBits(sc_logic_Z);
    }
}

void ThreeStateBusRegEnable::flipflop()
{
    registered = dataIn.read();
}

#endif // THREESTATEBUSREGENABLE_H
