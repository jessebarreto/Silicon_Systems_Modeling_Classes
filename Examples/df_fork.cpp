

#include <systemc.h>

template <class T>
SC_MODULE(DF_Fork)
{
    sc_fifo_in<T> in;
    sc_fifo_out<T> out1, out2;

    void proc ()
    {
        T val;
        while (true) {
            val = in.read();
            out1.write(val);
            out2.write(val);
        }
    }

    SC_CTOR(DF_Fork)
    {
        SC_THREAD(proc);
    }
};
