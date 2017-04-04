
#include "threestatebusreg.h"
#include "threestatebusregtb.h"

int main(int argc, char *argv[])
{

    ThreeStateBusWithRegister trisbus("TriStateBusReg");
    ThreeStateBusWithRegisterTb trisbustb("TriStateBusRegTb");

    sc_signal<bool> clk, readEnable;
    sc_signal<sc_lv<BUSSIZE> > inBus;
    sc_signal<sc_lv<BUSSIZE> > outBus;

    trisbus.clk(clk);               trisbustb.clk(clk);
    trisbus.readEnable(readEnable); trisbustb.readEnable(readEnable);
    trisbus.inBus(inBus);          trisbustb.inBus(inBus);
    trisbus.outBus(outBus);         trisbustb.outBus(outBus);


    sc_trace_file *wf = sc_create_vcd_trace_file("ThreeStateBus_Traces");
    sc_trace(wf, trisbustb.clk, "CLK");
    sc_trace(wf, trisbustb.readEnable, "ENABLE");
    sc_trace(wf, trisbustb.inBus, "IN");
    sc_trace(wf, trisbustb.outBus, "OUT");

    sc_start();
    sc_close_vcd_trace_file(wf);

    return 0;
}
