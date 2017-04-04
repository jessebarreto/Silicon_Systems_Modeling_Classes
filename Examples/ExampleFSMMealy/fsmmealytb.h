#include <systemc.h>

#ifndef FSMMEALYTB_H
#define FSMMEALYTB_H

SC_MODULE(FSMMealyTb)
{
    sc_out<bool> clk, reset;
    sc_out<bool> in1, in2;
    sc_in<bool> out1, out2;

    void driverClk();

    void driverPins();

    SC_CTOR(FSMMealyTb)
    {
        SC_THREAD(driverClk);

        SC_THREAD(driverPins);
    }
};

void FSMMealyTb::driverClk()
{
    bool clock = false;
    std::cout << "-----" << "\tCLK" << "\tRESET" << "\tIN1" << "\tIN2" << "\tOUT1" << "\tOUT2" << std::endl;
    for (int i = 0; i < 20; i++) {
        clk = clock;
        clock = !clock;
        wait(5, SC_NS);
        std::cout << sc_time_stamp() << "\t" << clk << "\t" << reset << "\t"
                  << in1 << "\t" << in2 << "\t"
                  << out1 << "\t" << out2 << "\t" << std::endl;
    }
}

void FSMMealyTb::driverPins()
{
    reset = true;
    in1 = false; in2 = false;
    wait(10, SC_NS);

    reset = false;
    in1 = false; in2 = false;
    wait(10, SC_NS);

    reset = false;
    in1 = true; in2 = false;
    wait(10, SC_NS);

    reset = false;
    in1 = true; in2 = true;
    wait(20, SC_NS);
}

#endif // FSMMEALYTB_H
