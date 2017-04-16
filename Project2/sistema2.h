#include <systemc.h>

#include "drivertb.h"
#include "printertb.h"

#include "temporizador.h"
#include "fsmsemaforo2methods.h"

#ifndef SISTEMA2_H
#define SISTEMA2_H

SC_MODULE(System2Top)
{
    // Componentes Testbench
    DriverTb driver;
    PrinterTb printer;

    // Componentes
    Temporizador temp;
    FSMSemaforo2Methods semaforo2;

    // Sinais
    sc_signal<bool> clk, reset;
    sc_signal<bool> sensorNorth, sensorSouth;
    sc_signal<bool> ic, il;
    sc_signal<bool> at;

    sc_signal<sc_uint<3> > AE;
    sc_signal<sc_uint<3> > VL;

    SC_CTOR(System2Top) :
        driver("Driver2"),
        printer("Printer2"),
        temp("Temporizador2"),
        semaforo2("Semaforo2")
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

        semaforo2.clk(clk);
        semaforo2.reset(reset);
        semaforo2.sensorNorth(sensorNorth);
        semaforo2.sensorSouth(sensorSouth);
        semaforo2.il(il);
        semaforo2.ic(ic);
        semaforo2.at(at);
        semaforo2.AE(AE);
        semaforo2.VL(VL);
    }
};
#endif // SISTEMA2_H
