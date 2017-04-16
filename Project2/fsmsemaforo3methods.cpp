#include "fsmsemaforo3methods.h"

void FSMSemaforo3Methods::_processState()
{
    if (reset.read()) {
        state = Idle;
    } else {
        state = nextState;
    }
}

void FSMSemaforo3Methods::_processOutput()
{
    if (reset.read()) {
        at = false;
        AE = Green;
        VL = Red;
    }

    switch (state) {
    case Idle:
        at = false;
        AE = Green;
        VL = Red;
        break;
    case AEGreenGo:
        at = true;
        AE = Green;
        VL = Red;
        break;
    case AEYellow:
        at = false;
        AE = Yellow;
        VL = Red;
        break;
    case AEYellowGo:
        at = true;
        AE = Yellow;
        VL = Red;
        break;
    case VLGreen:
        at = false;
        AE = Red;
        VL = Green;
        break;
    case VLGreenGo:
        at = true;
        AE = Red;
        VL = Green;
        break;
    case VLYellow:
        at = false;
        AE = Red;
        VL = Yellow;
        break;
    case VLYellowGo:
        at = true;
        AE = Red;
        VL = Yellow;
        break;
    default:
        at = false;
        AE = Green;
        VL = Red;
        break;
    }
}

void FSMSemaforo3Methods::_processNextState()
{
    if (reset.read()) {
        nextState = Idle;
    }

    switch (state) {
        case Idle:
            nextState = (sensorNorth.read() || sensorSouth.read()) ? AEGreenGo : Idle;
            break;
        case AEGreenGo:
            if (!(sensorNorth.read() || sensorSouth.read())) {
                nextState = Idle;
            } else if (il.read()) {
                nextState = AEYellow;
            } else {
                nextState = AEGreenGo;
            }
            break;
        case AEYellow:
            nextState = AEYellowGo;
            break;
        case AEYellowGo:
            nextState = (ic.read()) ? VLGreen : AEYellowGo;
            break;
        case VLGreen:
            nextState = VLGreenGo;
            break;
        case VLGreenGo:
            nextState = (il.read()) ? VLYellow : VLGreenGo;
            break;
        case VLYellow:
            nextState = VLYellowGo;
            break;
        case VLYellowGo:
            nextState = (ic.read()) ? Idle : VLYellowGo;
            break;
        default:
            nextState = Idle;
            break;
    }
}
