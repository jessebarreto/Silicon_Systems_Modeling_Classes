
#include "ffd.h"
#include "ffdtb.h"

int sc_main(int argc, char *argv[])
{

    FlipFlopD ffD("FFD");
    FlipFlopDTb ffDTb("FFD_Tb");

    sc_signal<bool> d, clk, q, bq;

    ffD.d(d);           ffDTb.d(d);
    ffD.clk(clk);       ffDTb.clk(clk);
    ffD.q(q);           ffDTb.q(q);
    ffD.not_q(bq);      ffDTb.not_q(bq);

    sc_trace_file *wf = sc_create_vcd_trace_file("FlipFlopD_Traces");
    sc_trace(wf, ffDTb.d, "D");
    sc_trace(wf, ffDTb.clk, "CLK");
    sc_trace(wf, ffDTb.q, "Q");
    sc_trace(wf, ffDTb.not_q, "notQ");

    sc_start(-1, SC_NS);
    sc_close_vcd_trace_file(wf);

    return 0;
}
