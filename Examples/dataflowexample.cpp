
#include "df_adder.cpp"
#include "df_const.cpp"
#include "df_fork.cpp"
#include "df_printer.cpp"

#define WORD_SIZE 4

int sc_main(int argc, char *argv[])
{

    sc_fifo<sc_int<WORD_SIZE> > s_const, s_adder, s_fork_p, s_fork_a;

    DF_Adder<sc_int<WORD_SIZE> > adder("DF_Adder");
    const sc_int<8> _constant = 1;
    DF_Const<sc_int<WORD_SIZE> > constant("DF_Const", _constant);
    DF_Fork<sc_int<WORD_SIZE> > fork("DF_Fork");
    DF_Printer<sc_int<WORD_SIZE> > printer("DF_Printer", 5);

    printer.in(s_fork_p);

    fork.out1(s_fork_a);
    fork.out2(s_fork_p);
    fork.in(s_adder);

    s_fork_a.write(sc_int<WORD_SIZE>(0));
    adder.out(s_adder);
    adder.in2(s_const);
    adder.in1(s_fork_a);

    constant.out(s_const);

    sc_start(-1, SC_NS);

    return 0;
}
