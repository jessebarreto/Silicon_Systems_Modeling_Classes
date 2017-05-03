#include <systemc.h>

#ifndef DRIVER_H
#define DRIVER_H

template<typename T>
SC_MODULE(Driver)
{
    sc_fifo_out<T> driverOut;

    void drive();

    SC_HAS_PROCESS(Driver);
    Driver(sc_module_name name, int width) :
        sc_module(name),
        _width(width)
    {
        _driverValue = 0;

        SC_THREAD(drive);
    }

private:
    int _width;
    T _driverValue;
};

template<typename T>
void Driver<T>::drive()
{
    for (int i = 0; i < _width; i++) {
        driverOut.write(_driverValue);
        wait(0, SC_NS);
    }
}

#endif // DRIVER_H
