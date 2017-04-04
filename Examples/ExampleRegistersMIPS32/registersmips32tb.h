
#include <systemc.h>

#ifndef REGISTERSMIPS32TB_H
#define REGISTERSMIPS32TB_H

SC_MODULE(RegistersMIPS32Tb)
{
    sc_out<sc_uint<32> > dataIn;
    sc_out<sc_uint<5> > addressIn1, addressIn2, addressWrite;
    sc_out<bool> clk, writeEnable;
    sc_in<sc_uint<32> > dataOut1, dataOut2;

    void runClk();

    void runDriver();

    SC_CTOR(RegistersMIPS32Tb)
    {
        SC_THREAD(runClk);

        SC_THREAD(runDriver);
    }
};

void RegistersMIPS32Tb::runDriver()
{
    dataIn = 32; addressIn1 = 0; addressIn2 = 0; addressWrite = 1; writeEnable = true;
    wait(20, SC_NS);

    dataIn = 64; addressIn1 = 0; addressIn2 = 0; addressWrite = 4; writeEnable = true;
    wait(20, SC_NS);

    dataIn = 128; addressIn1 = 1; addressIn2 = 4; addressWrite = 8; writeEnable = true;
    wait(20, SC_NS);

    dataIn = 32; addressIn1 = 4; addressIn2 = 8; addressWrite = 16; writeEnable = false;
    wait(20, SC_NS);

    dataIn = 32; addressIn1 = 8; addressIn2 = 4; addressWrite = 16; writeEnable = false;
    wait(20, SC_NS);
}

void RegistersMIPS32Tb::runClk()
{
    std::cout << "-----" << "\tCLK"<< "\tWE" << "\tDATA_IN" << "\tADDR1" << "\tADDR2" << "\tADDRW"
              << "\tOUT1" << "\tOUT2"  << std::endl;
    bool clock = false;
    for (int i = 0; i < 20; i++) {
        clk = clock;
        clock = !clock;
        wait(5, SC_NS);
        std::cout << sc_time_stamp() << "\t" << clk << "\t" << writeEnable << "\t" << dataIn << "\t"
                  << addressIn1 << "\t" << addressIn2 << "\t" << addressWrite << "\t"
                  << dataOut1 << "\t" << dataOut2 << std::endl;

    }
}


#endif // REGISTERSMIPS32TB_H
