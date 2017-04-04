
#include "register.h"


#ifndef REGISTERTB_H
#define REGISTERTB_H

SC_MODULE(RegisterTb)
{

    sc_in<sc_uint<WIDTH> > dataOut;
    sc_out<sc_uint<WIDTH> > dataIn;
    sc_out<bool> clk;

    void clk_run();

    void data_run();

    SC_CTOR(RegisterTb)
    {
        SC_THREAD(clk_run);

        SC_THREAD(data_run);
    }
};

void RegisterTb::data_run()
{

    for (unsigned int i = 1; i < 4; i++) {
        dataIn = i;
        wait(4, SC_NS);
    }
}

void RegisterTb::clk_run()
{
    std::cout << "-----" << "\tCLK" << "\tDATA_IN" << "\tDATA_OUT" << std::endl;

    bool clock;
    for (int i = 0; i < 8; i++) {
        clk = clock;
        clock = !clock;
        wait(2, SC_NS);
        std::cout << sc_time_stamp() << "\t" << clk << "\t" << dataIn.read().to_uint() << "\t" << dataOut.read().to_uint() << std::endl;
    }
}

#endif // REGISTERTB_H
