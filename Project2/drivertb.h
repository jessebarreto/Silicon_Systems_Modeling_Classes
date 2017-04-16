#include <systemc.h>

#ifndef DRIVERTB_H
#define DRIVERTB_H

#define CLK_PERIOD 10

SC_MODULE(DriverTb)
{
    sc_out<bool> clk, reset;
    sc_out<bool> sensorNorth, sensorSouth;

    SC_CTOR(DriverTb)
    {
        _clock = false;
        SC_THREAD(_driverClk);

        SC_THREAD(_driverSignals);
    }

private:
    bool _clock;
    void _driverClk();

    void _driverSignals();
};

#endif // DRIVERTB_H
