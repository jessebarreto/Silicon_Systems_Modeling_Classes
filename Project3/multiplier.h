#include <systemc.h>

#ifndef MULTIPLIER_H
#define MULTIPLIER_H

template<typename T>
SC_MODULE(Multiplier)
{
    // Vector's element
    sc_in<T> vectorElement;

    sc_fifo_in<T> matrixElements;
    sc_fifo_in<T> driverElements;

    sc_fifo_out<T> resultsOut;

    void multiply();

    SC_CTOR(Multiplier)
    {
        SC_THREAD(multiply);
    }
};

template<typename T>
void Multiplier<T>::multiply()
{
    for (;;) {
        resultsOut.write(matrixElements.read() * vectorElement.read() + driverElements.read());
    }
}

#endif // MULTIPLIER_H
