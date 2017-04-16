#include "printertb.h"

void PrinterTb::_process()
{
    std::cout << sc_time_stamp() << "\t" << clk << "\t" << reset << "\t"
              << sensorNorth << "\t" << sensorSouth << "\t"
              << ic << "\t" << il << "\t" << at << "\t"
              << AE << "\t" << VL << "\t"
              << std::endl;
}
