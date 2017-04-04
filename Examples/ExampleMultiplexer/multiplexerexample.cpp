

#include "mux.h"
#include "muxtb.h"

int sc_main(int argc, char *argv[])
{

    Multiplexer4in8bits mux("Mux");
    Multiplexer4in8bitsTb muxtb("MuxTb");

    sc_signal<sc_uint<8> > _1, _2, _3, _4, _out;
    sc_signal<sc_uint<2> >  _sel;

    mux.in1(_1);        muxtb.in1(_1);
    mux.in2(_2);        muxtb.in2(_2);
    mux.in3(_3);        muxtb.in3(_3);
    mux.in4(_4);        muxtb.in4(_4);
    mux.sel(_sel);      muxtb.sel(_sel);
    mux.mux_out(_out);  muxtb.mux_out(_out);

    sc_trace_file *wf = sc_create_vcd_trace_file("Multiplexer_Testbench");
    sc_trace(wf, muxtb.in1, "in1");
    sc_trace(wf, muxtb.in2, "in2");
    sc_trace(wf, muxtb.in3, "in3");
    sc_trace(wf, muxtb.in4, "in4");
    sc_trace(wf, muxtb.sel, "sel");
    sc_trace(wf, muxtb.mux_out, "out");

    sc_start();
    sc_close_vcd_trace_file(wf);

    return 0;
}
