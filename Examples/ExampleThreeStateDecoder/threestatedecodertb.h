#include <systemc.h>

#ifndef THREESTATEDECODERTB_H
#define THREESTATEDECODERTB_H

SC_MODULE(ThreeStateDecoderTb)
{
    sc_out<bool> enable;
    sc_out<sc_uint<3> > sel;
    sc_in<sc_lv<8> > outDec;

    void runDriver();

    SC_CTOR(ThreeStateDecoderTb)
    {
        SC_THREAD(runDriver);
    }
};

void ThreeStateDecoderTb::runDriver()
{
    std::cout << "-----" << "\tENABLE" << "\tSEL" << "\tOUT" << std::endl;

    enable = false; sel = 0;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << enable << "\t" << sel << "\t" << outDec << "\t" << std::endl;

    enable = false; sel = 1;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << enable << "\t" << sel << "\t" << outDec << "\t" << std::endl;

    for (int i = 0; i < 8; i++)
    {
        enable = true; sel = i;
        wait(5, SC_NS);
        std::cout << sc_time_stamp() << "\t" << enable << "\t" << sel << "\t" << outDec << "\t" << std::endl;
    }
}

#endif // THREESTATEDECODERTB_H
