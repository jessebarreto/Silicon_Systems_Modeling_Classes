#include "threestatebusreg.h"

#ifndef THREESTATEBUSREGTB_H
#define THREESTATEBUSREGTB_H

SC_MODULE(ThreeStateBusWithRegisterTb)
{
    sc_out<bool> clk, readEnable;
    sc_out<sc_lv<BUSSIZE> > inBus;
    sc_in<sc_lv<BUSSIZE> > outBus;

    void runDriver();

    void runClk();

    SC_CTOR(ThreeStateBusWithRegisterTb)
    {
        SC_THREAD(runClk);

        SC_THREAD(runDriver);
    }

private:
    sc_lv<BUSSIZE> _fillBits(sc_dt::sc_logic value);
};

sc_lv<BUSSIZE> ThreeStateBusWithRegisterTb::_fillBits(sc_logic value)
{
    sc_lv<BUSSIZE> filled;
    for (int i = 0; i < BUSSIZE; i++) {
        filled[i] = value;
    }
    return filled;
}

void ThreeStateBusWithRegisterTb::runDriver()
{
    readEnable = false; inBus.write(_fillBits(sc_logic_0));
    wait(5, SC_NS);

    readEnable = false; inBus.write(_fillBits(sc_logic_1));
    wait(5, SC_NS);

    readEnable = true; inBus.write(_fillBits(sc_logic_0));
    wait(5, SC_NS);

    readEnable = true; inBus.write(_fillBits(sc_logic_1));
    wait(5, SC_NS);
}

void ThreeStateBusWithRegisterTb::runClk()
{
    std::cout << "-----" << "\tCLK" << "\tENABLE" << "\tIN" << "\tOUT" << std::endl;
    bool clock = false;
    for (int i = 0; i < 20; i++) {
        clk = clock;
        clock = !clock;
        wait(2, SC_NS);
        std::cout << sc_time_stamp() << "\t" << clk << "\t" << readEnable << "\t" << inBus << "\t" << outBus << "\t" << std::endl;
    }
}

#endif // THREESTATEBUSREGTB_H
