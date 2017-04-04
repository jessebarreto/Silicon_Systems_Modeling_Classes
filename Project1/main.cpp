/******************************************************************************************
 * Universidade de Brasília – UnB
 * Instituto de Ciências Exatas – IE
 * Departamento de Ciência da Computação – CIC
 * Modelagem de Sistemas em Silicio – Professor Ricardo Jacobi
 *
 * Projeto 1 – Objetivo
 *  Projetar e simular uma ULA com tamanho de palavra parametrizável.
 *
 * Nome: Jessé Barreto de Barros
 * Matrícula: 17/0067033
 ******************************************************************************************
*/

#include "sistema.h"


int sc_main (int argc, char *argv[])
{
    top tbAndSystem("top");

    sc_trace_file* trace_file = sc_create_vcd_trace_file("waveform");
    sc_trace(trace_file, tbAndSystem.opcode, "opcode");
    sc_trace(trace_file, tbAndSystem.A, "A");
    sc_trace(trace_file, tbAndSystem.B, "B");
    sc_trace(trace_file, tbAndSystem.Z, "Z");
    sc_trace(trace_file, tbAndSystem.zero, "zero");

    std::cout << "Starting ..." << std::endl;
    sc_start (100, SC_PS);

    sc_close_vcd_trace_file(trace_file);
    cout << "Saved waveform.vcd" << endl;

    return 0;
	
}
