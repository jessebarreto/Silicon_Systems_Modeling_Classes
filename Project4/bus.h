#ifndef BUS_H
#define BUS_H

#include <systemc.h>

#include "ibusmaster.h"
#include "ibusslave.h"

class Bus : public sc_module, public IBusSlave, public IBusMaster
{
protected:
    sc_event _masterReqWEvent, _masterRecWEvent, _masterReqREvent, _masterRecREvent;
    sc_event _slaveReqWEvent, _slaveRecWEvent, _slaveReqREvent, _slaveRecREvent;

    uint16_t *_dataRef;
    unsigned _curAddress;
    uint16_t _readValue, _writeValue;

    sc_mutex masterLocker, slaveLocker;

    void runRead();

    void runWrite();

public:
    SC_HAS_PROCESS(Bus);
    Bus(sc_module_name name) : sc_module(name)
    {
        SC_THREAD(runRead);

        SC_THREAD(runWrite);
    }

    //////////////////////////////////////////////////////////
    // Slave Requests/Receives Functions
    sc_event& writeSlaveReqEvent(uint16_t *data);

    sc_event& readSlaveReqEvent();

    sc_event& writeSlaveRecEvent();

    sc_event& readSlaveRecEvent(uint16_t *data);
    //////////////////////////////////////////////////////
    // Master Requests/Receives Functions
    sc_event& writeMasterReqEvent(unsigned address, uint16_t &newValue);

    sc_event& readMasterReqEvent(unsigned address);

    sc_event& writeMasterRecEvent(uint16_t *data);

    sc_event& readMasterRecEvent(uint16_t *data);
    ////////////////////////////////////////////////////
};

void Bus::runRead()
{
    for (;;) {
        wait(_masterReqREvent);
        _slaveReqREvent.notify();
        wait(_slaveRecREvent);

        _readValue = _dataRef[_curAddress];

        _masterRecREvent.notify();
        masterLocker.unlock();
        slaveLocker.unlock();
    }
}

void Bus::runWrite()
{
    for (;;) {
        wait(_masterReqWEvent);
        _slaveReqWEvent.notify();
        wait(_slaveRecWEvent);
        _masterRecWEvent.notify();
        masterLocker.unlock();
        slaveLocker.unlock();
    }
}

sc_event& Bus::readSlaveReqEvent()
{
    slaveLocker.lock();
    return _slaveReqREvent;
}

sc_event& Bus::writeSlaveReqEvent(uint16_t *data)
{
    slaveLocker.lock();
    _dataRef = data;
    _dataRef[_curAddress] = _writeValue;
    return _slaveReqWEvent;
}

sc_event& Bus::readSlaveRecEvent(uint16_t *data)
{
    _dataRef = data;
    return _slaveRecREvent;
}

sc_event& Bus::writeSlaveRecEvent()
{
    return _slaveRecWEvent;
}

// Master
sc_event& Bus::writeMasterReqEvent(unsigned address, uint16_t& newValue)
{
    masterLocker.lock();
    _curAddress = address;
    _writeValue = newValue;
    return _masterReqWEvent;
}

sc_event& Bus::readMasterReqEvent(unsigned address)
{
    masterLocker.lock();
    _curAddress = address;
    return _masterReqREvent;
}

sc_event& Bus::writeMasterRecEvent(uint16_t *data)
{
    return _masterRecWEvent;
}

sc_event& Bus::readMasterRecEvent(uint16_t *data)
{
    *data = _readValue;
    return _masterRecREvent;
}

#endif // BUS_H
