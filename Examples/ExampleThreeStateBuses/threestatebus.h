#include <systemc.h>

#ifndef THREESTATEBUS_H
#define THREESTATEBUS_H

#define BUSSIZE 8

SC_MODULE(ThreeStateBus)
{
    sc_in<bool> read1Enable, read2Enable;
    sc_in_rv<BUSSIZE> in1Bus, in2Bus;
    sc_out_rv<BUSSIZE> outBus;

    void process1();

    void process2();

    SC_CTOR(ThreeStateBus)
    {
        SC_METHOD(process1);
        sensitive << read1Enable << in1Bus;

        SC_METHOD(process2);
        sensitive << read2Enable << in2Bus;
    }
};

void ThreeStateBus::process1()
{
    if (read1Enable.read()) {
        outBus.write(in1Bus.read());
    } else {
        sc_lv<BUSSIZE> hi;
        for (int i = 0; i < BUSSIZE; i ++) {
            hi[i] = sc_logic_Z;
        }
        outBus.write(hi);
    }
}

void ThreeStateBus::process2()
{
    if (read2Enable.read()) {
        outBus.write(in2Bus.read());
    } else {
        sc_lv<BUSSIZE> hi;
        for (int i = 0; i < BUSSIZE; i ++) {
            hi[i] = sc_logic_Z;
        }
        outBus.write(hi);
    }
}

#endif // THREESTATEBUS_H
