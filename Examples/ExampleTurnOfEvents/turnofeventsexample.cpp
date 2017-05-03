#include <systemc.h>

#include "turnofevents.h"

int sc_main(int argc, char *argv[])
{
    TurnOfEvents turn("Module!");

    sc_start(-1, SC_NS);

    return 0;
}
