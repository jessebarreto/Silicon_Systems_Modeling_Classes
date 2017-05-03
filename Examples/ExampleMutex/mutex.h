#include <systemc.h>

#ifndef MUTEX_H
#define MUTEX_H

SC_MODULE(Carro)
{
    sc_mutex chave;

    void pai();

    void filho();

    SC_CTOR(Carro)
    {
        SC_THREAD(pai);

        SC_THREAD(filho);
    }
};

void Carro::pai()
{
    wait(std::rand() % 10, SC_MS);
    std::cout << sc_time_stamp() << " - pai busca a chave" << std::endl;
    chave.lock();
    std::cout << sc_time_stamp() << " - pai pega a chave." << std::endl;
    std::cout << sc_time_stamp() << " - pai dirigindo..." << std::endl;
    wait(std::rand() % 10, SC_MS);
    std::cout << sc_time_stamp() << " - pai liberando..." << std::endl;
    chave.unlock();
}

void Carro::filho()
{
    wait(std::rand() % 10, SC_MS);
    std::cout << sc_time_stamp() << " - filho busca a chave" << std::endl;
    chave.lock();
    std::cout << sc_time_stamp() << " - filho pega a chave." << std::endl;
    std::cout << sc_time_stamp() << " - filho dirigindo..." << std::endl;
    wait(std::rand() % 10, SC_MS);
    std::cout << sc_time_stamp() << " - filho liberando..." << std::endl;
    chave.unlock();
}

#endif // MUTEX_H
