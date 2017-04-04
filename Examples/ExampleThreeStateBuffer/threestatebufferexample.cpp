
#include "threestatebuffer.h"
#include "threestatebuffertb.h"

int sc_main(int argc, char *argv[])
{

    ThreeStateBuffer trisbuffer("3StateBuffer");
    ThreeStateBufferTb trisbuffertb("3StateBufferTb");

    sc_signal<bool> enable;
    sc_signal<sc_logic> inBuffer;
    sc_signal<sc_logic> outBuffer;

    trisbuffer.enable(enable);          trisbuffertb.enable(enable);
    trisbuffer.inBuffer(inBuffer);      trisbuffertb.inBuffer(inBuffer);
    trisbuffer.outBuffer(outBuffer);    trisbuffertb.outBuffer(outBuffer);

    sc_trace_file *wf = sc_create_vcd_trace_file("ThreeStateBuffer_Traces");
    sc_trace(wf, trisbuffer.enable, "ENABLE");
    sc_trace(wf, trisbuffer.inBuffer, "IN");
    sc_trace(wf, trisbuffer.outBuffer, "OUT");

    sc_start();
    sc_close_vcd_trace_file(wf);

    return 0;
}
