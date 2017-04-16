#include "temporizador.h"



void Temporizador::_process()
{
    if (!enable.read()) {
        _counter = 0;
        ic = false;
        il = false;
    } else {
        _counter++;
        if (_counter == SHORT_DURATION) {
            ic = true;
        } else {
            ic = false;
        }
        if (_counter == LONG_DURATION) {
            il = true;
            _counter = 0;
        } else {
            il = false;
        }
    }
}
