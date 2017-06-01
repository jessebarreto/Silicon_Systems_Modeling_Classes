#ifndef SIMPLE_BUS_CUSTOM_MEM_H
#define SIMPLE_BUS_CUSTOM_MEM_H

#include <systemc.h>

#include "simple_bus_types.h"
#include "simple_bus_slave_if.h"

#define DEBUG 1

class simple_bus_custom_mem :
        public sc_module,
        public simple_bus_slave_if
{
    int *_memory;
    unsigned _memoryStartAddress;
    unsigned _memoryEndAddress;

public:
    // Constructor
    simple_bus_custom_mem(sc_module_name name, unsigned startAddress, unsigned endAddress);

    ~simple_bus_custom_mem();

    // Slave interface
    simple_bus_status read(int *data, unsigned int address);
    simple_bus_status write(int *data, unsigned int address);
    unsigned int start_address() const;
    unsigned int end_address() const;

    // Has Fast Slave Interface Too
    bool direct_read(int *data, unsigned int address);
    bool direct_write(int *data, unsigned int address);
};

simple_bus_custom_mem::simple_bus_custom_mem(sc_module_name name, unsigned startAddress, unsigned endAddress) :
    sc_module(name),
    _memoryStartAddress(startAddress),
    _memoryEndAddress(endAddress)
{
    // Check for faults
    sc_assert(_memoryStartAddress <= _memoryEndAddress);
    sc_assert((_memoryEndAddress - _memoryStartAddress + 1) % 4 == 0);

    // Memory Size
    unsigned int memorySize = (_memoryEndAddress - _memoryStartAddress) / 4;

    // Fill Memory
    _memory = new int [memorySize];
    for (int i = 0; i < memorySize; i++) {
        _memory[i] = 0;
    }
}

simple_bus_custom_mem::~simple_bus_custom_mem()
{
    if (_memory) {
        delete [] _memory;
        _memory = NULL;
    }
}

simple_bus_status simple_bus_custom_mem::read(int *data, unsigned int address)
{
#if DEBUG
    std::cout << "Leitura @" << address << std::endl;
#endif
    *data = _memory[(address - _memoryStartAddress) / 4];
    return SIMPLE_BUS_OK;
}

simple_bus_status simple_bus_custom_mem::write(int *data, unsigned int address)
{
#if DEBUG
    std::cout << "Escrita @" << address << ", " << *data << std::endl;
#endif
    _memory[(address - _memoryStartAddress) / 4] = *data;
    return SIMPLE_BUS_OK;
}

unsigned int simple_bus_custom_mem::start_address() const
{
    return _memoryStartAddress;
}

unsigned int simple_bus_custom_mem::end_address() const
{
    return _memoryEndAddress;
}

bool simple_bus_custom_mem::direct_read(int *data, unsigned int address)
{
  return (read(data, address) == SIMPLE_BUS_OK);
}

bool simple_bus_custom_mem::direct_write(int *data, unsigned int address)
{
  return (write(data, address) == SIMPLE_BUS_OK);
}

#endif // SIMPLE_BUS_CUSTOM_MEM_H
