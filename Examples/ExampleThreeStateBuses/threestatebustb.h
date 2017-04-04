
#include "threestatebus.h"

#ifndef THREESTATEBUSTB_H
#define THREESTATEBUSTB_H

SC_MODULE(ThreeStateBusTb)
{
    sc_out<bool> read1Enable, read2Enable;
    sc_out_rv<BUSSIZE> in1Bus, in2Bus;
    sc_in_rv<BUSSIZE> outBus;

    void runDriver();

    SC_CTOR(ThreeStateBusTb)
    {
        SC_THREAD(runDriver);
    }
};

void ThreeStateBusTb::runDriver()
{
    std::cout << "-----" << "\tENABLE1" << "\tENABLE2" << "\tIN1" << "\tIN2" << "\tOUT" << std::endl;

    read1Enable.write(false); read2Enable.write(false);
    in1Bus.write(1); in2Bus.write(3);
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << read1Enable << "\t" << read2Enable << "\t"
              << in1Bus << "\t" << in2Bus << "\t" << outBus << std::endl;

    read1Enable.write(false); read2Enable.write(true);
    in1Bus.write(1); in2Bus.write(3);
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << read1Enable << "\t" << read2Enable << "\t"
              << in1Bus << "\t" << in2Bus << "\t" << outBus << std::endl;

    read1Enable.write(true); read2Enable.write(false);
    in1Bus.write(1); in2Bus.write(3);
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << read1Enable << "\t" << read2Enable << "\t"
              << in1Bus << "\t" << in2Bus << "\t" << outBus << std::endl;

    read1Enable.write(true); read2Enable.write(true);
    in1Bus.write(1); in2Bus.write(3);
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << read1Enable << "\t" << read2Enable << "\t"
              << in1Bus << "\t" << in2Bus << "\t" << outBus << std::endl;

    read1Enable.write(false); read2Enable.write(false);
    in1Bus.write(1); in2Bus.write(3);
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << read1Enable << "\t" << read2Enable << "\t"
              << in1Bus << "\t" << in2Bus << "\t" << outBus << std::endl;
}

#endif // THREESTATEBUSTB_H
