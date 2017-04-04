#include "threestatebusregenable.h"

#ifndef THREESTATEBUSREGENABLETB_H
#define THREESTATEBUSREGENABLETB_H

SC_MODULE(ThreeStateBusRegEnableTb)
{
    sc_out<bool> enable, clk;
    sc_out<sc_lv<BUSSIZE> > dataIn;
    sc_in<sc_lv<BUSSIZE> > dataOut;

    void driverPins();

    void driverClk();

    SC_CTOR(ThreeStateBusRegEnableTb)
    {
        SC_THREAD(driverPins);

        SC_THREAD(driverClk);
    }
};

void ThreeStateBusRegEnableTb::driverClk()
{
    std::cout << "-----" << "\tCLK" << "\tENABLE" << "\tIN" << "\tOUT" << std::endl;
    bool clock = false;
    for (int i = 0; i < 20; i++) {
        clk = clock;
        clock = !clock;
        wait(5, SC_NS);
        std::cout << sc_time_stamp() << "\t" << clk << "\t" << enable << "\t" << dataIn << "\t" << dataOut << "\t" << std::endl;
    }
}

void ThreeStateBusRegEnableTb::driverPins()
{
    enable = false; dataIn.write(0);
    wait(20, SC_NS);

    enable = false; dataIn.write(1);
    wait(20, SC_NS);

    enable = true; dataIn.write(0);
    wait(20, SC_NS);

    enable = true; dataIn.write(1);
    wait(20, SC_NS);
}

#endif // THREESTATEBUSREGENABLETB_H
