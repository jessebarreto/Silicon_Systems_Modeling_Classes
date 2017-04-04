
#include <systemc.h>

template <class T>
SC_MODULE(DF_Const) {
    sc_fifo_out<T> out;
    T _const;

    void proc ()
    {
        while (true) {
            out.write(_const);
        }
    }

    SC_HAS_PROCESS (DF_Const);

    DF_Const(sc_module_name n, const T& c):
        sc_module(n),
        _const(c)
    {
        SC_THREAD(proc);
    }
};
