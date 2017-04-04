
#include "register.h"
#include "registertb.h"

int sc_main(int argc, char *argv[])
{

    Register reg("Register");
    RegisterTb regtb("RegisterTb");

    sc_signal<sc_uint<WIDTH> > dataIn, dataOut;
    sc_signal<bool> clk;

    reg.dataIn(dataIn);     regtb.dataIn(dataIn);
    reg.dataOut(dataOut);   regtb.dataOut(dataOut);
    reg.clk(clk);           regtb.clk(clk);

    sc_trace_file *wf = sc_create_vcd_trace_file("Register_Traces");
    sc_trace(wf, reg.dataIn, "dataIn");
    sc_trace(wf, reg.dataIn, "dataOut");
    sc_trace(wf, reg.clk, "clk");

    sc_start();
    sc_close_vcd_trace_file(wf);

    return 0;
}
