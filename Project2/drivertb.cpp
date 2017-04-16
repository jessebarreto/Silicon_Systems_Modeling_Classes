#include "drivertb.h"


void DriverTb::_driverClk()
{
    for (;;) {
        clk = _clock;
        _clock = !_clock;
        wait(CLK_PERIOD/2, SC_NS);
    }
}

void DriverTb::_driverSignals()
{
    reset = true;
    sensorNorth = false; sensorSouth = false;
    wait(20, SC_NS);

    reset = false;
    sensorNorth = false; sensorSouth = false;
    wait(20, SC_NS);

    reset = false;
    sensorNorth = false; sensorSouth = true;
    wait(140, SC_NS);

    reset = false;
    sensorNorth = true; sensorSouth = false;
    wait(140, SC_NS);

    reset = true;
    sensorNorth = true; sensorSouth = false;
    wait(20, SC_NS);
}
