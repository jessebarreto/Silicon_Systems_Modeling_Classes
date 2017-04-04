
#include "registersmips32.h"
#include "registersmips32tb.h"


int sc_main(int argc, char *argv[])
{
    RegistersMIPS32 breg("BReg");
    RegistersMIPS32Tb bregtb("BRegTB");

    sc_signal<sc_uint<32> > dataIn;
    sc_signal<sc_uint<5> > addressIn1, addressIn2, addressWrite;
    sc_signal<bool> clk, writeEnable;
    sc_signal<sc_uint<32> > dataOut1, dataOut2;

    breg.clk(clk);                      bregtb.clk(clk);
    breg.dataIn(dataIn);                bregtb.dataIn(dataIn);
    breg.addressIn1(addressIn1);        bregtb.addressIn1(addressIn1);
    breg.addressIn2(addressIn2);        bregtb.addressIn2(addressIn2);
    breg.addressWrite(addressWrite);    bregtb.addressWrite(addressWrite);
    breg.writeEnable(writeEnable);      bregtb.writeEnable(writeEnable);
    breg.dataOut1(dataOut1);            bregtb.dataOut1(dataOut1);
    breg.dataOut2(dataOut2);            bregtb.dataOut2(dataOut2);


    sc_trace_file *wf = sc_create_vcd_trace_file("BReg_Traces");
    sc_trace(wf, bregtb.clk, "clk");
    sc_trace(wf, bregtb.dataIn, "dataIn");
    sc_trace(wf, bregtb.addressIn1, "addressIn1");
    sc_trace(wf, bregtb.addressIn2, "addressIn2");
    sc_trace(wf, bregtb.addressWrite, "addressWrite");
    sc_trace(wf, bregtb.writeEnable, "writeEnable");
    sc_trace(wf, bregtb.dataOut1, "dataOut1");
    sc_trace(wf, bregtb.dataOut2, "dataOut2");

    sc_start();

    return 0;
}
