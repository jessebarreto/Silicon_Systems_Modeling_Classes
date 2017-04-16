#include <systemc.h>

#include "fsmsemaforo3methods.h"

#ifndef PRINTERTB_H
#define PRINTERTB_H

SC_MODULE(PrinterTb)
{
    sc_in<bool> sensorNorth, sensorSouth, reset, clk;
    sc_in<bool> ic, il, at;

    sc_in<sc_uint<3> > AE, VL;

    SC_CTOR(PrinterTb)
    {
        std::cout << "-----"
                  << "\tCLK"
                  << "\tRESET"
                  << "\tSENSORN"
                  << "\tSENSORS"
                  << "\tIC"
                  << "\tIL"
                  << "\tAT"
                  << "\tAE"
                  << "\tVL"
                  << std::endl;

        SC_METHOD(_process);
        sensitive << reset << sensorNorth << sensorSouth
                  << ic << il << at
                  << AE << VL;
    }
private:
    void _process();
};

#endif // PRINTERTB_H
