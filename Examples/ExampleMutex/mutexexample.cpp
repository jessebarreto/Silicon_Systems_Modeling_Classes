#include <systemc.h>

#include "mutex.h"

int sc_main(int argc, char *argv[])
{
    Carro carro("Carro!");

    sc_start();

    return 0;
}
