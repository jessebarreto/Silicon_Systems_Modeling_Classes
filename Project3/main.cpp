
#include <systemc.h>

#include "sistema.h"

#define TIPO int

int sc_main(int argc, char *argv[])
{
    const TIPO VECTOR_ELEMENTS[] = {1, 1, 1, 1};
    const TIPO MATRIX_ELEMENTS[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    const int WIDTH = 4;
    const std::vector<TIPO> MATRIX(MATRIX_ELEMENTS, MATRIX_ELEMENTS+WIDTH*WIDTH);
    const std::vector<TIPO> VECTOR(VECTOR_ELEMENTS, VECTOR_ELEMENTS+WIDTH);

    System<TIPO> topModule("Sistema", WIDTH, MATRIX , VECTOR);

    sc_start(100, SC_NS);

    return 0;
}


//const TIPO VECTOR_ELEMENTS[] = {1, 1, 1};
//const TIPO MATRIX_ELEMENTS[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
