#include <systemc.h>

#define BUSSIZE 8

#ifndef THREESTATEBUSREG_H
#define THREESTATEBUSREG_H

SC_MODULE(ThreeStateBusWithRegister)
{
    sc_in<bool> clk, readEnable;
    sc_in<sc_lv<BUSSIZE> > inBus;
    sc_out<sc_lv<BUSSIZE> > outBus;

    void process();

    SC_CTOR(ThreeStateBusWithRegister)
    {
        SC_METHOD(process);
        sensitive << clk.pos();
    }
};

void ThreeStateBusWithRegister::process()
{
    sc_lv<BUSSIZE> output(sc_logic_Z);

    if (readEnable.read()) {
        outBus = inBus;
    } else {
        outBus = output;
    }
}

#endif // THREESTATEBUSREG_H
