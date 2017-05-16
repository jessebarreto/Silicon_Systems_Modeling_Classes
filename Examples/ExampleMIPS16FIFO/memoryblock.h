#include <systemc.h>

#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H

SC_MODULE(MemoryBlock)
{
    // FIFOs
    sc_fifo_in<unsigned> address_in;
    sc_fifo_in<uint16_t> data_in;
    sc_fifo_out<unsigned> address_out;
    sc_fifo_out<uint16_t> data_out;

    void thread();

    SC_HAS_PROCESS(MemoryBlock);

    MemoryBlock(sc_module_name name, const unsigned& memorySize) : sc_module_name(name)
    {
        _memorySize = memorySize;
        _memodyData = new uint16_t(_memorySize);

        SC_THREAD(thread);
    }

private:
    unsigned _memorySize;
    uint16_t* _memodyData;

};

void MemoryBlock::thread()
{
    for (;;) {

    }
}


#endif // MEMORYBLOCK_H
