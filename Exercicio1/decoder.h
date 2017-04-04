#ifndef DECODER_H
#define DECODER_H


#include "systemc.h"

SC_MODULE(decoder)
{
private:
    sc_uint<32> data;

public:
    sc_in <sc_uint<5> > i;
    sc_out <sc_uint<32> > dec;

    SC_CTOR(decoder)
    {
        SC_METHOD(exec);
        sensitive << i;
    }

    void exec();
};

#endif // DECODER_H
