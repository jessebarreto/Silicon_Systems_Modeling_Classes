
#include "fsmmealy.h"
#include "fsmmealytb.h"

int sc_main(int argc, char *argv[])
{
    FSMMealy fsm("FSM");
    FSMMealyTb fsmtb("FSMTb");

    sc_signal<bool> clk, reset;
    sc_signal<bool> in1, in2;
    sc_signal<bool> out1, out2;

    fsm.clk(clk);       fsmtb.clk(clk);
    fsm.reset(reset);   fsmtb.reset(reset);
    fsm.in1(in1);       fsmtb.in1(in1);
    fsm.in2(in2);       fsmtb.in2(in2);
    fsm.out1(out1);     fsmtb.out1(out1);
    fsm.out2(out2);     fsmtb.out2(out2);

    sc_trace_file *wf = sc_create_vcd_trace_file("FSMMealy_Traces");
    sc_trace(wf, fsmtb.clk, "CLK");
    sc_trace(wf, fsmtb.reset, "RESET");
    sc_trace(wf, fsmtb.in1, "IN1");
    sc_trace(wf, fsmtb.in2, "IN2");
    sc_trace(wf, fsmtb.out1, "OUT1");
    sc_trace(wf, fsmtb.out2, "OUT2");

    sc_start();
    sc_close_vcd_trace_file(wf);

    return 0;
}
