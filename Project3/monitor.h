#include <systemc.h>

#ifndef MONITOR_H
#define MONITOR_H

template<typename T>
SC_MODULE(Monitor)
{
    sc_fifo_in<T> values;

    void printer();

    SC_HAS_PROCESS(Monitor);
    Monitor(sc_module_name name, const std::vector<T>& vector, const std::vector<T>& matrix)
    {
        std::cout << "Begin..." << std::endl;
        // Print Matrix
        std::cout << "Matrix: \n[ ";
        for (int i = 0; i < vector.size(); i++) {
            for (int j = 0; j < vector.size(); j++) {
                std::cout << "\t" << matrix.at(j + i * vector.size()) << " ";
            }
            std::cout << " " << std::endl;
        }
        std::cout << "]" << std::endl;

        // Print Vector
        std::cout << "Vector: \n [ ";
        for (int i = 0; i < vector.size(); i++) {
            std::cout << vector.at(i) << " ";
        }
        std::cout << "]" << std::endl;

        std::cout << "Output vector: \n [ ";
        SC_THREAD(printer);
    }


    ~Monitor()
    {
        std::cout << "]" << std::endl;
    }
};

template<typename T>
void Monitor<T>::printer()
{
    for (;;) {
        T value = values.read();
        std::cout << value << " ";
    }
}

#endif // MONITOR_H
