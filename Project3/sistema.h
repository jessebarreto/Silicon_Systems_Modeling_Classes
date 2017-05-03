#include <systemc.h>
#include <vector>
#include <sstream>

#include "driver.h"
#include "multiplier.h"
#include "monitor.h"

#ifndef SISTEMA_H
#define SISTEMA_H

template<typename T>
SC_MODULE(System)
{
    // FIFOs
    std::vector<sc_fifo<T>* > matrixElements;
    std::vector<sc_fifo<T>* > multipliersFIFO;
    sc_fifo<T> s_monitor, s_driver;

    // Signals
    std::vector<sc_signal<T>* > vectorElements;

    // Components
    std::vector<Multiplier<T>* > multipliers;
    Monitor<T> monitor;
    Driver<T> driver;

    SC_HAS_PROCESS(System);
    System(sc_module_name name, int width, const std::vector<T>& matrix, const std::vector<T>& vector) :
        sc_module(name),
        _width(width),
        _matrix(matrix),
        _vector(vector),
        monitor("MONITOR", vector, matrix),
        driver("DRIVER", width)

    {
        // Leave the program if dimensions are wrong
        if (matrix.size() != width * width || vector.size() != width) {
            std::cout << "[ERROR] Dimension provided has wrong size." << std::endl;
            throw std::exception();
        }

        // Fill Matrix
        _fillMatrixFIFOs();

        // Fill Vectors
        _fillVectorSignals();

        // Fill Multipliers and Connect them
        bool begin = true;
        for (int i = 0; i < _width; i++) {
            std::stringstream ss;
            ss << "Multiplier_" << i;
            Multiplier<T>* mul = new Multiplier<T>(ss.str().c_str());
            sc_fifo<T>* fifo = new sc_fifo<T>();

            if (begin) {
                mul->driverElements(s_driver);
                mul->matrixElements(*matrixElements.at(i));
                mul->vectorElement(*vectorElements.at(i));
                mul->resultsOut(*fifo);
                begin = false;
            } else if (i == _width - 1) {
                mul->driverElements(*multipliersFIFO.back());
                mul->matrixElements(*matrixElements.at(i));
                mul->vectorElement(*vectorElements.at(i));
                mul->resultsOut(s_monitor);
            } else {
                mul->driverElements(*multipliersFIFO.back());
                mul->matrixElements(*matrixElements.at(i));
                mul->vectorElement(*vectorElements.at(i));
                mul->resultsOut(*fifo);
            }
            multipliers.push_back(mul);
            multipliersFIFO.push_back(fifo);
        }

        // Connect Components
        driver.driverOut(s_driver);
        monitor.values(s_monitor);

    }

    // Destructor
    ~System()
    {
        // Clear matrix
        typename std::vector<sc_fifo<T>* >::iterator it = matrixElements.begin();
        for (;it != matrixElements.end(); it++) {
            delete *it;
        }
        matrixElements.clear();

        // Clear vector
        typename std::vector<sc_signal<T>* >::iterator itv = vectorElements.begin();
        for (;itv != vectorElements.end(); itv++) {
            delete *itv;
        }
        vectorElements.clear();

        // Clear Multipliers
        typename std::vector<Multiplier<T>* >::iterator itm = multipliers.begin();
        for (;itm != multipliers.end(); itm++) {
            delete *itm;
        }
        multipliers.clear();

        // Clear Multipliers FIFOs
        typename std::vector<sc_fifo<T>* >::iterator itmm = multipliersFIFO.begin();
        for (;itmm != multipliersFIFO.end(); itmm++) {
            delete *itmm;
        }
        multipliersFIFO.clear();
    }

private:
    // Dimensions
    int _width;

    // Matrix
    std::vector<T> _matrix;
    void _fillMatrixFIFOs();

    // Vector
    std::vector<T> _vector;
    void _fillVectorSignals();
};

template<typename T>
void System<T>::_fillMatrixFIFOs()
{
    for (int i = 0; i < _width; i++) {
        sc_fifo<T>* fifo = new sc_fifo<T>();

        for (int j = 0; j < _width; j++) {
            fifo->write(_matrix.at(i + j * _width));
        }
        matrixElements.push_back(fifo);
    }
}

template<typename T>
void System<T>::_fillVectorSignals()
{
    for (int i = 0; i < _width; i++) {
        sc_signal<T>* vectorSignal = new sc_signal<T>();
        vectorSignal->write(_vector.at(i));
        vectorElements.push_back(vectorSignal);
    }
}

#endif // SISTEMA_H
