
#include "threestatedecoder.h"
#include "threestatedecodertb.h"

int sc_main(int argc, char *argv[])
{
    ThreeStateDecoder tristatedec("3StateDec");
    ThreeStateDecoderTb tristatedectb("3StateDecTb");

    sc_signal<bool> enable;
    sc_signal<sc_uint<3> > sel;
    sc_signal<sc_lv<8> > outDec;

    tristatedec.enable(enable); tristatedectb.enable(enable);
    tristatedec.sel(sel);       tristatedectb.sel(sel);
    tristatedec.outDec(outDec); tristatedectb.outDec(outDec);

    sc_trace_file *wf = sc_create_vcd_trace_file("ThreeStateDecoder_Traces");
    sc_trace(wf, tristatedectb.enable, "ENABLE");
    sc_trace(wf, tristatedectb.sel, "SEL");
    sc_trace(wf, tristatedectb.outDec, "OUT");

    sc_start();
    sc_close_vcd_trace_file(wf);

    return 0;
}
