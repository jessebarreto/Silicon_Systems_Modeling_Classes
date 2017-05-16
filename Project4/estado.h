
#ifndef ESTADO_H
#define ESTADO_H

#include <stdint.h>

class Estado
{
public:
    uint16_t instruction, pc;
    uint8_t opcode, rs, rt, rd, k4, k8;

    Estado()
    {
        instruction = 0;
        pc = 0;
        opcode = 0;
        rs = 0;
        rt = 0;
        rd = 0;
        k4 = 0;
        k8 = 0;
    }
};

#endif // ESTADO_H
