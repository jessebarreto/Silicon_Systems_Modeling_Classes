
#include "threestatebusregenable.h"
#include "threestatebusregenabletb.h"

int sc_main(int argc, char *argv[])
{
    ThreeStateBusRegEnable trisbus("TriStateBus");
    ThreeStateBusRegEnableTb trisbustb("TriStateBusTb");

    sc_signal<bool> enable, clk;
    sc_signal<sc_lv<BUSSIZE> > dataIn;
    sc_signal<sc_lv<BUSSIZE> > dataOut;

    trisbus.clk(clk);               trisbustb.clk(clk);
    trisbus.enable(enable);         trisbustb.enable(enable);
    trisbus.dataIn(dataIn);         trisbustb.dataIn(dataIn);
    trisbus.dataOut(dataOut);       trisbustb.dataOut(dataOut);

    sc_trace_file *wf = sc_create_vcd_trace_file("ThreeStateBusRegEnable_Traces");
    sc_trace(wf, trisbustb.clk, "CLK");
    sc_trace(wf, trisbustb.enable, "ENABLE");
    sc_trace(wf, trisbustb.dataIn, "IN");
    sc_trace(wf, trisbustb.dataOut, "OUT");

    sc_start();
    sc_close_vcd_trace_file(wf);

    return 0;
}
