
#include "hf_adder.h"
#include "hf_adder_testbench.h"


int sc_main(int argc, char *argv[])
{
    HalfAdder halfAdderModule("HalfAdder");
    HalfAdderTb halfAdderTbModule("HalfAdderTb");

    sc_signal<bool> x, y, sum, carryOut;

    halfAdderModule.x(x);
    halfAdderModule.y(y);
    halfAdderModule.sum(sum);
    halfAdderModule.carry_out(carryOut);

    halfAdderTbModule.x(x);
    halfAdderTbModule.y(y);
    halfAdderTbModule.sum(sum);
    halfAdderTbModule.carry_out(carryOut);


    sc_trace_file *wf = sc_create_vcd_trace_file("hf_adder_testbench");
    sc_trace(wf, halfAdderTbModule.x, "x");
    sc_trace(wf, halfAdderTbModule.y, "y");
    sc_trace(wf, halfAdderTbModule.sum, "sum");
    sc_trace(wf, halfAdderTbModule.carry_out, "carry_out");

    sc_start(-1, SC_NS);
    sc_close_vcd_trace_file(wf);

    return 0;
}
