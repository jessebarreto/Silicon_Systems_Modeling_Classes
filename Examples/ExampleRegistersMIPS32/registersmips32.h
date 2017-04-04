#include <systemc.h>

#ifndef REGISTERSMIPS32_H
#define REGISTERSMIPS32_H

SC_MODULE(RegistersMIPS32)
{
    sc_in<sc_uint<32> > dataIn;
    sc_in<sc_uint<5> > addressIn1, addressIn2, addressWrite;
    sc_in<bool> clk, writeEnable;
    sc_out<sc_uint<32> > dataOut1, dataOut2;

    void write();

    void read();

    SC_CTOR(RegistersMIPS32)
    {
        SC_METHOD(write);
        sensitive << clk.pos();

        SC_METHOD(read);
        sensitive << addressIn1 << addressIn2 << addressWrite << clk << writeEnable;
    }

private:
    sc_uint<32> data[32];
};

void RegistersMIPS32::write()
{
    if (writeEnable.read())
        data[addressWrite.read()] = dataIn;
}

void RegistersMIPS32::read()
{
    dataOut1 = addressIn1.read() == 0 ? (sc_uint<32>)(0) : data[addressIn1.read()];
    dataOut2 = addressIn2.read() == 0 ? (sc_uint<32>)(0) : data[addressIn2.read()];
}

#endif // REGISTERSMIPS32_H
