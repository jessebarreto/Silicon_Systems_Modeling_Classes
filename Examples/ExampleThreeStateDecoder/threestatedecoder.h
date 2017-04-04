
#include <systemc.h>

#ifndef THREESTATEDECODER_H
#define THREESTATEDECODER_H

SC_MODULE(ThreeStateDecoder)
{
    sc_in<bool> enable;
    sc_in<sc_uint<3> > sel;
    sc_out<sc_lv<8> > outDec;

    void process();

    SC_CTOR(ThreeStateDecoder)
    {
        SC_METHOD(process);
        sensitive << enable << sel;
    }
};

void ThreeStateDecoder::process()
{
    sc_lv<8> saida = "00000000";

    if (!enable) {
        saida = "ZZZZZZZZ";
    } else {
        saida[sel.read().to_uint()] = '1';
    }
    outDec = saida;
}

#endif // THREESTATEDECODER_H
