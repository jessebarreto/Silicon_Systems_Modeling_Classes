
#include <systemc.h>

template <class T>
SC_MODULE(DF_Adder)
{
    sc_fifo_in<T> in1, in2;
    sc_fifo_out<T> out;

    void proc ()
    {
        while (true) {
            wait(10, SC_NS);
            out.write(in1.read() + in2.read());
        }
    }

    SC_CTOR(DF_Adder)
    {
        SC_THREAD(proc);
    }
};
