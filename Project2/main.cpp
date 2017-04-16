/******************************************************************************************
 * Universidade de Brasília – UnB
 * Instituto de Ciências Exatas – IE
 * Departamento de Ciência da Computação – CIC
 * Modelagem de Sistemas em Silicio – Professor Ricardo Jacobi
 *
 * Projeto 2 – Objetivo
 * Controlador de Tráfego utilizando Máquinas de Estados Finitos (FSM).
 *
 * Nome: Jessé Barreto de Barros
 * Matrícula: 17/0067033
 ******************************************************************************************
*/

#include <systemc.h>

#include "sistema.h"
#include "sistema2.h"

int sc_main(int argc, char *argv[])
{
    SystemTop topComponent("Component");
    System2Top topComponent2("Component2");

    sc_trace_file *trace_file = sc_create_vcd_trace_file("waveform_Project2");
    sc_trace(trace_file, topComponent.clk, "CLK");
    sc_trace(trace_file, topComponent.reset, "RESET");
    sc_trace(trace_file, topComponent.sensorNorth, "SENSORN");
    sc_trace(trace_file, topComponent.sensorSouth, "SENSORS");
    sc_trace(trace_file, topComponent.ic, "IC");
    sc_trace(trace_file, topComponent.il, "IL");
    sc_trace(trace_file, topComponent.at, "AT");
    sc_trace(trace_file, topComponent.AE, "AE");
    sc_trace(trace_file, topComponent.VL, "VL");

    sc_trace_file *trace_file2 = sc_create_vcd_trace_file("waveform2_Project2");
    sc_trace(trace_file2, topComponent2.clk, "CLK");
    sc_trace(trace_file2, topComponent2.reset, "RESET");
    sc_trace(trace_file2, topComponent2.sensorNorth, "SENSORN");
    sc_trace(trace_file2, topComponent2.sensorSouth, "SENSORS");
    sc_trace(trace_file2, topComponent2.ic, "IC");
    sc_trace(trace_file2, topComponent2.il, "IL");
    sc_trace(trace_file2, topComponent2.at, "AT");
    sc_trace(trace_file2, topComponent2.AE, "AE");
    sc_trace(trace_file2, topComponent2.VL, "VL");

    std::cout << "Starting ..." << std::endl;
    sc_start (400, SC_NS);

    sc_close_vcd_trace_file(trace_file);
    sc_close_vcd_trace_file(trace_file2);
    cout << "Project2_FSM_Semaforo3.vcd" << endl;

    return 0;
}
