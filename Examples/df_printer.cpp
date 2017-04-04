
#include <systemc.h>
#include <iostream>

using namespace std;

template <class T>
SC_MODULE(DF_Printer)
{
    // IO
    sc_fifo_in<T> in;

    // local
    unsigned _niter;
    bool _done;

    SC_HAS_PROCESS(DF_Printer);

    DF_Printer(sc_module_name n, unsigned niter) :
        sc_module(n), _niter(niter),
        _done(false)
    {
        SC_THREAD(proc);
    }

    void proc()
    {
        for (unsigned i=0; i < _niter; i++) {
            T val = in.read();
            cout << name() << " " << sc_time_stamp() << " " << val << endl;
        }
        _done = true;
        return;
    }
        ~DF_Printer()
        {
            if (!_done) {
                cout << name() << " not done yet." << endl;
            }
        }
};
