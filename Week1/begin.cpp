#include <systemc.h>

SC_MODULE (begin_1st_test)
{
    SC_CTOR (begin_1st_test)
    {

    }

    void printMsg()
    {
        cout << "test 1st commit!\n";
    }
};

int sc_main(int argc, char *argv[])
{
    begin_1st_test begin("BEGIN");
    begin.printMsg();
    return 0;
}
