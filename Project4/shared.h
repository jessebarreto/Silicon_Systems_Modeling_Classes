/*
 *  shared.h
 *  riscene++
 *
 *  Created by Ricardo Jacobi on 29/4/14.
 *  Copyright 2014 Universidade de Brasilia. All rights reserved.
 *
 */

#ifndef SHARED_H
#define SHARED_H

#include <stdarg.h>
#include <stdint.h>

// Debug Variable
#define DEBUG 1

const int NUMBEROFREGISTERS = 16;

const uint16_t MAX_MEM = 1024;

const uint16_t write_int = 512;

enum i_FORMAT {
        TIPO_R=4, TIPO_J=3
};

enum INSTRUCTIONS {
        i_ADD	= 0x2,
        i_SUB	= 0x3,
        i_ADDi	= 0x8,
        i_SHIFT	= 0x9,
        i_AND	= 0x4,
        i_OR	= 0x5,
        i_NOT	= 0xA,
        i_XOR	= 0x6,
        i_SLT	= 0x7,
        i_LW	= 0x0,
        i_SW	= 0x1,
        i_LUI	= 0xB,
        i_BEQ	= 0xC,
        i_BNE	= 0xD,
        i_J		= 0xE,
        i_JAL	= 0xF
};

enum REGISTERS {
    $zero = 0x0,
    $t0 = 0x1,
    $t1 = 0x2,
    $t2 = 0x3,
    $a0 = 0x4,
    $a1 = 0x5,
    $a2 = 0x6,
    $s0	= 0x7,
    $s1	= 0x8,
    $s2	= 0x9,
    $s3	= 0xA,
    $int = 0xB,
    $gp = 0xC,
    $sp = 0xD,
    $pc = 0xE,
    $ra = 0xF
};

uint16_t gerainst(int n, ...) {
        short inst = 0;

        va_list ap;

        va_start(ap, n);

        switch (n) {
                case TIPO_R:
                        inst |= (va_arg(ap, int ) & 0xF) << 12;
                        inst |= (va_arg(ap, int ) & 0xF) << 8;
                        inst |= (va_arg(ap, int ) & 0xF) << 4;
                        inst |= (va_arg(ap, int ) & 0xF);
                        break;
                case TIPO_J:
                        inst |= (va_arg(ap, int ) & 0xF) << 12;
                        inst |= (va_arg(ap, int ) & 0xF) << 8;
                        inst |= (va_arg(ap, int ) & 0xFF);
                        break;
                default:
                        break;
        }
        return inst;
}

void loadProgram(uint16_t *memory)
{
    int i = 0;
    // lui $s0, 0
    memory[i] = gerainst(TIPO_J, i_LUI, $s0, 1);
    i++;
    // shift $s0, -4
    memory[i] = gerainst(TIPO_J, i_SHIFT, $s0, -4);
    i++;
    // and $t2, $t2, $zero
    memory[i] = gerainst(TIPO_R, i_AND, $zero, $t2, $t2);
    i++;
    // addi $t2, 0xFE
    memory[i] = gerainst(TIPO_J, i_ADDi, $t2, 0xFE);
    i++;
    // add $s1, $s0, $zero
    memory[i] = gerainst(TIPO_R, i_ADD, $zero, $s0, $s1);
    i++;
    // addi $s0, 8
    memory[i] = gerainst(TIPO_J, i_ADDi, $s0, 0x08);
    i++;
    // addi $s1, 4
    memory[i] = gerainst(TIPO_J, i_ADDi, $s1, 0x04);
    i++;
    // add $s2, $s1, $s0
    memory[i] = gerainst(TIPO_R, i_ADD, $s0, $s1, $s2);
    i++;
    // sub $s3, $s1, $s0
    memory[i] = gerainst(TIPO_R, i_SUB, $s0, $s1, $s3);
    i++;
    // and $t1, $s0, $zero
    memory[i] = gerainst(TIPO_R, i_AND, $zero, $s0, $t1);
    i++;
    // addi $t1, 50
    memory[i] = gerainst(TIPO_J, i_ADDi, $t1, 50);
    i++;
    // sw $t1, $zero, $s0
    memory[i] = gerainst(TIPO_R, i_SW, $t1, $zero, $s0);
    i++;
    // addi $t1, 1
    memory[i] = gerainst(TIPO_J, i_ADDi, $t1, 1);
    i++;
    // sw $t1, $zero, $s1
    memory[i] = gerainst(TIPO_R, i_SW, $t1, $zero, $s1);
    i++;
    // addi $t1, 1
    memory[i] = gerainst(TIPO_J, i_ADDi, $t1, 1);
    i++;
    // sw $t1, $zero, $s2
    memory[i] = gerainst(TIPO_R, i_SW, $t1, $zero, $s2);
    i++;
    // addi $t1, 1
    memory[i] = gerainst(TIPO_J, i_ADDi, $t1, 1);
    i++;
    // sw $t1, $zero, $s3
    memory[i] = gerainst(TIPO_R, i_SW, $t1, $zero, $s3);
    i++;
    // addi $t1, 1
    memory[i] = gerainst(TIPO_J, i_ADDi, $t1, 1);
    i++;
    // shift $s1, -1
    memory[i] = gerainst(TIPO_J, i_SHIFT, $s1, -1);
    i++;
    // sw $t1, $zero, $s1
    memory[i] = gerainst(TIPO_R, i_SW, $t1, $zero, $s1);
    i++;
    // addi $t1, 1
    memory[i] = gerainst(TIPO_J, i_ADDi, $t1, 1);
    i++;
    // j $zero, 50 - HALT RISC SIMULATION
    memory[i] = gerainst(TIPO_J, i_J, $zero, 0xFF - i - 2);
    i++;

    for (;i < MAX_MEM; i++) {
        memory[i] = 0x00;
    }

//    /* addi $1, 0 */
//    memory[0] = gerainst(TIPO_J, i_ADDi, 1, 0 );
//    /* addi $1, 8 */
//    memory[1] = gerainst(TIPO_J, i_ADDi, 1, 8 );
//    /* addi $2, -12 */
//    memory[2] = gerainst(TIPO_J, i_ADDi, 2, -12 );
//    /* add $3, $2, $1 */
//    memory[3] = gerainst(TIPO_R, i_ADD, 1, 2, 3 );
//    /* sub $4, $2, $1 */
//    memory[4] = gerainst(TIPO_R, i_SUB, 2, 3, 4 );
//    /* add $5, $0, $1 */
//    memory[5] = gerainst(TIPO_R, i_ADD, 1, 0, 5 );
//    /* shift $5, 2 */
//    memory[6] = gerainst(TIPO_J, i_SHIFT, 5, 2);
//    /* add $6, $0, $1 */
//    memory[7] = gerainst(TIPO_R, i_ADD, 1, 0, 6 );
//    /* shift $6, -4 */
//    memory[8] = gerainst(TIPO_J, i_SHIFT, 6, -4);
//    /* lui $7, FF */
//    memory[9] = gerainst(TIPO_J, i_LUI, 7, 0xFF);
//    /* and $8, $7, $4 */
//    memory[10] = gerainst(TIPO_R, i_AND, 4, 7, 8);
//    /* add $9, $0, $8 */
//    memory[11] = gerainst(TIPO_R, i_ADD, 8, 0, 9 );
//    /* not $9 */
//    memory[12] = gerainst(TIPO_R, i_NOT, 9, 0, 0 );
//    /* xor $10, $4, $7  */
//    memory[13] = gerainst(TIPO_R, i_XOR, 4, 7, 10 );
//    /* slt $11, $5, $1  */
//    memory[14] = gerainst(TIPO_R, i_SLT, 5, 1, 11 );
//    /* sw $5, $0, $6  */
//    memory[15] = gerainst(TIPO_R, i_SW, 6, 0, 5 );
//    /* lw $12, $0, $0  */
//    memory[16] = gerainst(TIPO_R, i_LW, 6, 0, 12 );
//    /* jal 20  */
//    memory[17] = gerainst(TIPO_J, i_JAL, 0, 20 );
//    /* beq $0, $1, 5  */
//    memory[18] = gerainst(TIPO_R, i_BEQ, 0, 1, 5 );
//    /* jr 15  */
//    memory[19] = gerainst(TIPO_R, i_BNE, 0, 1, 7 );
//    /* jr 20  */
//    memory[20] = gerainst(TIPO_J, i_J, 15, 0 );

}

void dump_breg(uint16_t *regBankRef) {
    for (int i=0; i<16; i++) {
        printf("BREG[%2d] = \t%4d \t\t\t%4x\n", i, regBankRef[i], regBankRef[i]);
    }
}

void dump_mem(uint16_t *mem, int start, int end, char format) {
    switch (format) {
        case 'h':
        case 'H':
            for (int i = start; i <= end; i++)
                printf("%x \t%x\n", i, mem[i]);
            break;
        case 'd':
        case 'D':
            for (int i = start; i <= end; i++)
                printf("%x \t%d\n", i, mem[i]);
            break;
        default:
            break;
    }
}


#endif // SHARED_H
