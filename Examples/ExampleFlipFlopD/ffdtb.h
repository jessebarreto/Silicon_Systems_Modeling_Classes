#include <systemc.h>

#ifndef FFDTB_H
#define FFDTB_H

SC_MODULE(FlipFlopDTb)
{
    sc_out<bool> d, clk;
    sc_in<bool> q, not_q;

    void acionar();

    void clock_activator();

    SC_CTOR(FlipFlopDTb)
    {
        SC_THREAD(clock_activator);
        SC_THREAD(acionar);
    }
};

void FlipFlopDTb::acionar()
{
    bool state = false;

    std::cout << "-----" << "\tCLK" << "\tD" << "\tQ" << "\tnotQ" << std::endl;

    for (int i = 0; i < 2; i++) {
        d = state;
        state = !state;
        wait(4, SC_NS);
    }
}

void FlipFlopDTb::clock_activator()
{
    bool clock = false;

    for (int i = 0; i < 5; i++) {
        clk = clock;
        clock = !clock;
        wait(2, SC_NS);
        std::cout << sc_time_stamp() << "\t" << clk << "\t" << d << "\t" << q << "\t" << not_q << std::endl;
    }
}

#endif // FFDTB_H
