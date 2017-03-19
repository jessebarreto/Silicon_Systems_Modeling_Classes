
#include "systemc.h"

#define DEBUG true

SC_MODULE (counter)
{
    // Pins
    sc_in_clk clk;
    sc_in<bool> reset;
    sc_in<bool> enable;
    sc_out<sc_uint<4> > cnt_out;

    // Local variables
    sc_uint<4> cnt;

    SC_CTOR (counter)
    {
        SC_METHOD(addCounter);
        sensitive << reset;
        sensitive << clk.pos();
    }

    void addCounter()
    {
        if (reset.read() == 1) {
            cnt = 0;
            cnt_out.write(cnt);
        } else if (enable.read() == 1) {
            cnt++;
            cnt_out.write(cnt);
            // DEBUG
            if (DEBUG) {
                std::cout << "@" << sc_time_stamp() << " :: Incremented Cnt " << cnt_out.read() << std::endl;
            }
        }
    }
};
