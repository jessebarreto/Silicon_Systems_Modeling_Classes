
#include <systemc.h>

#ifndef ULA32TB_H
#define ULA32TB_H

SC_MODULE(Ula32Tb)
{
    // Pins
    sc_out<int32_t> a, b;
    sc_out<int8_t> control;
    sc_in<int32_t> z;
    sc_in<bool> zero;

    void runDriver();

    SC_CTOR(Ula32Tb)
    {
        SC_THREAD(runDriver);
    }
};

void Ula32Tb::runDriver()
{
    std::cout << "-----" << "\tA"<< "\tB" << "\tCONTROL" << "\tZ" << "\tZERO" << std::endl;

    a.write(20); b.write(10); control.write(0);
    wait(20, SC_NS);
    std::cout << sc_time_stamp() << "\t" << a << "\t" << b << "\t" << control << "\t" << z << "\t" << zero << "\t" << std::endl;

    a.write(10); b.write(20); control.write(1);
    wait(20, SC_NS);
    std::cout << sc_time_stamp() << "\t" << a << "\t" << b << "\t" << control << "\t" << z << "\t" << zero << "\t" << std::endl;

    a.write(20); b.write(10); control.write(2);
    wait(20, SC_NS);
    std::cout << sc_time_stamp() << "\t" << a << "\t" << b << "\t" << control << "\t" << z << "\t" << zero << "\t" << std::endl;

    a.write(10); b.write(20); control.write(6);
    wait(20, SC_NS);
    std::cout << sc_time_stamp() << "\t" << a << "\t" << b << "\t" << control << "\t" << z << "\t" << zero << "\t" << std::endl;

    a.write(20); b.write(10); control.write(7);
    wait(20, SC_NS);
    std::cout << sc_time_stamp() << "\t" << a << "\t" << b << "\t" << control << "\t" << z << "\t" << zero << "\t" << std::endl;

    a.write(20); b.write(20); control.write(12);
    wait(20, SC_NS);
    std::cout << sc_time_stamp() << "\t" << a << "\t" << b << "\t" << control << "\t" << z << "\t" << zero << "\t" << std::endl;

    a.write(10); b.write(25); control.write(0);
    wait(20, SC_NS);
    std::cout << sc_time_stamp() << "\t" << a << "\t" << b << "\t" << control << "\t" << z << "\t" << zero << "\t" << std::endl;
}

#endif // ULA32TB_H
