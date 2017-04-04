
#include "threestatebus.h"
#include "threestatebustb.h"

int sc_main(int argc, char *argv[])
{

    ThreeStateBus trisbus("TriStateBus");
    ThreeStateBusTb trisbustb("TriStateBusTb");

    sc_signal<bool> read1Enable, read2Enable;
    sc_signal_rv<BUSSIZE> in1Bus, in2Bus;
    sc_signal_rv<BUSSIZE> outBus;

    trisbus.read1Enable(read1Enable); trisbustb.read1Enable(read1Enable);
    trisbus.read2Enable(read2Enable); trisbustb.read2Enable(read2Enable);
    trisbus.in1Bus(in1Bus);           trisbustb.in1Bus(in1Bus);
    trisbus.in2Bus(in2Bus);           trisbustb.in2Bus(in2Bus);
    trisbus.outBus(outBus);           trisbustb.outBus(outBus);

    sc_trace_file *wf = sc_create_vcd_trace_file("ThreeStateBus_Traces");
    sc_trace(wf, trisbustb.read1Enable, "ENABLE1");
    sc_trace(wf, trisbustb.read2Enable, "ENABLE2");
    sc_trace(wf, trisbustb.in1Bus, "IN1");
    sc_trace(wf, trisbustb.in2Bus, "IN2");
    sc_trace(wf, trisbustb.outBus, "OUT");

    sc_start();
    sc_close_vcd_trace_file(wf);

    return 0;
}
