#include "fsmsemaforo2methods.h"

void FSMSemaforo2Methods::_processOutputNextState()
{
    if (reset.read()) {
        nextState = Idle;
        at = false;
        AE = Green;
        VL = Red;
    }

    switch (state) {
        case Idle:
            nextState = (sensorNorth.read() || sensorSouth.read()) ? AEGreenGo : Idle;
            at = false;
            AE = Green;
            VL = Red;
            break;
        case AEGreenGo:
            if (!(sensorNorth.read() || sensorSouth.read())) {
                nextState = Idle;
            } else if (il.read()) {
                nextState = AEYellow;
            } else {
                nextState = AEGreenGo;
            }
            at = true;
            AE = Green;
            VL = Red;
            break;
        case AEYellow:
            nextState = AEYellowGo;
            at = false;
            AE = Yellow;
            VL = Red;
            break;
        case AEYellowGo:
            nextState = (ic.read()) ? VLGreen : AEYellowGo;
            at = true;
            AE = Yellow;
            VL = Red;
            break;
        case VLGreen:
            nextState = VLGreenGo;
            at = false;
            AE = Red;
            VL = Green;
            break;
        case VLGreenGo:
            nextState = (il.read()) ? VLYellow : VLGreenGo;
            at = true;
            AE = Red;
            VL = Green;
            break;
        case VLYellow:
            nextState = VLYellowGo;
            at = false;
            AE = Red;
            VL = Yellow;
            break;
        case VLYellowGo:
            nextState = (ic.read()) ? Idle : VLYellowGo;
            at = true;
            AE = Red;
            VL = Yellow;
            break;
        default:
            nextState = Idle;
            at = false;
            AE = Green;
            VL = Red;
            break;
    }
}

void FSMSemaforo2Methods::_processState()
{
    if (reset.read()) {
        state = Idle;
    } else {
        state = nextState;
    }
}
