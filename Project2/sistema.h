#include <systemc.h>

#include "drivertb.h"
#include "printertb.h"

#include "temporizador.h"
#include "fsmsemaforo3methods.h"

#ifndef SISTEMA_H
#define SISTEMA_H

SC_MODULE(SystemTop)
{
    // Componentes Testbench
    DriverTb driver;
    PrinterTb printer;

    // Componentes
    Temporizador temp;
    FSMSemaforo3Methods semaforo3;

    // Sinais
    sc_signal<bool> clk, reset;
    sc_signal<bool> sensorNorth, sensorSouth;
    sc_signal<bool> ic, il;
    sc_signal<bool> at;

    sc_signal<sc_uint<3> > AE;
    sc_signal<sc_uint<3> > VL;

    SC_CTOR(SystemTop) :
        driver("Driver"),
        printer("Printer"),
        temp("Temporizador"),
        semaforo3("Semaforo3")
    {
        // Conexoes
        driver.clk(clk);
        driver.reset(reset);
        driver.sensorNorth(sensorNorth);
        driver.sensorSouth(sensorSouth);

        printer.clk(clk);
        printer.reset(reset);
        printer.sensorNorth(sensorNorth);
        printer.sensorSouth(sensorSouth);
        printer.ic(ic);
        printer.il(il);
        printer.at(at);
        printer.AE(AE);
        printer.VL(VL);

        temp.clk(clk);
        temp.enable(at);
        temp.ic(ic);
        temp.il(il);

        semaforo3.clk(clk);
        semaforo3.reset(reset);
        semaforo3.sensorNorth(sensorNorth);
        semaforo3.sensorSouth(sensorSouth);
        semaforo3.il(il);
        semaforo3.ic(ic);
        semaforo3.at(at);
        semaforo3.AE(AE);
        semaforo3.VL(VL);
    }
};

#endif // SISTEMA_H
