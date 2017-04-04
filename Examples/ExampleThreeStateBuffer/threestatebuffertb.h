
#include <systemc.h>

#ifndef THREESTATEBUFFERTB_H
#define THREESTATEBUFFERTB_H

SC_MODULE(ThreeStateBufferTb)
{
    sc_out<bool> enable;
    sc_out<sc_logic> inBuffer;
    sc_in<sc_logic> outBuffer;

    void runDriver();

    SC_CTOR(ThreeStateBufferTb)
    {
        SC_THREAD(runDriver);
    }
};

void ThreeStateBufferTb::runDriver()
{
    std::cout << "-----" << "\tENABLE" << "\tIN" << "\tOUT" << std::endl;

    inBuffer = sc_logic_0; enable = true;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << enable << "\t" << inBuffer << "\t" << outBuffer << "\t" << std::endl;

    inBuffer = sc_logic_1; enable = true;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << enable << "\t" << inBuffer << "\t" << outBuffer << "\t" << std::endl;

    inBuffer = sc_logic_0; enable = false;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << enable << "\t" << inBuffer << "\t" << outBuffer << "\t" << std::endl;

    inBuffer = sc_logic_1; enable = false;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << enable << "\t" << inBuffer << "\t" << outBuffer << "\t" << std::endl;
}

#endif // THREESTATEBUFFERTB_H
