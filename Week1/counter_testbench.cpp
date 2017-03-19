#include <systemc.h>

#include "counter.cpp"

int sc_main(int argc, char *argv[])
{
    sc_signal<bool> clk;
    sc_signal<bool> reset;
    sc_signal<bool> enable;
    sc_signal<sc_uint<4> > counter_out;

    int i = 0;

    // Connect the counter
    counter counter1("COUNTER");
    counter1.clk(clk);
    counter1.reset(reset);
    counter1.enable(enable);
    counter1.cnt_out(counter_out);

    sc_start(1, SC_NS);

    sc_trace_file *writeFile = sc_create_vcd_trace_file("counter");
    // Dump the signals
    sc_trace(writeFile, clk, "clk");
    sc_trace(writeFile, reset, "reset");
    sc_trace(writeFile, enable, "enable");
    sc_trace(writeFile, counter_out, "Count");

    // Initialize variables
    reset = 0;
    enable = 0;
    for (i = 0; i < 5; i++) {
        clk = 0;
        sc_start(1, SC_NS);
        clk = 1;
        sc_start(1, SC_NS);
    }

    // Asserting reset
    reset = 1;
    if (DEBUG) {
        std::cout << "@" << sc_time_stamp() << " Asserting reset\n" << std::endl;
    }
    for ( i = 0; i < 10; i++)
    {
        clk = 0;
        sc_start(1, SC_NS);
        clk = 1;
        sc_start(1, SC_NS);
    }

    // De-Asserting reset
    reset = 0;
    if (DEBUG) {
        std::cout << "@" << sc_time_stamp() << " De-Asserting reset\n" << std::endl;
    }
    for (i = 0; i < 5; i++) {
        clk = 0;
        sc_start(1, SC_NS);
        clk = 1;
        sc_start(1, SC_NS);
    }

    // Asserting enable
    enable = 1;
    if (DEBUG) {
        std::cout << "@" << sc_time_stamp() << " Asserting enable\n" << std::endl;
    }
    for (i = 0; i < 20; i++) {
        clk = 0;
        sc_start(1, SC_NS);
        clk = 1;
        sc_start(1, SC_NS);
    }

    // De-Asserting enable
    enable = 0;
    if (DEBUG) {
        std::cout << "@" << sc_time_stamp() << " Finishing Simulation\n" << std::endl;
    }
    sc_close_vcd_trace_file(writeFile);
    return 0;
}
