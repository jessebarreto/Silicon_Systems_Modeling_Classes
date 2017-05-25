/*
 * - noc_common.h
 * 
* 
 * Created by José Adalberto F. Gualeve  on 07/07/15.
 * Copyright 2015 - All rights reserved 
*/
#ifndef noc_common_h
#define noc_common_h
#include "systemc.h"



const int mem_size = 0x00010000;
const int flit_size = 32;   // bits
const int buffer_size = 32; // uint32_l's
const int pkg_size = 8;     // flits
const int debug = 1;

typedef sc_uint<flit_size> flit_t;
typedef sc_uint<flit_size/2> flit1_2t;
typedef sc_uint<flit_size/4> flit1_4t;

const flit1_2t CMD_SB=0x0028, // command store a byte 0b0000.0000.0010.1000
    CMD_SH=0x0029, // command store a half word       0b0000.0000.0010.1001
    CMD_SW=0x002B, // command store a word            0b0000.0000.0010.1011
    CMD_LB=0x0020, // command load a byte             0b0000.0000.0010.0000
    CMD_LH=0x0021, // command load a half word        0b0000.0000.0010.0001
    CMD_LW=0x0023; // command load a word             0b0000.0000.0010.0011

// control inline, used to code debuging
inline void passo(const char* id, int x ) 
{    
    cout <<"In " << id << ",checked "<<x<<endl;
}


#endif
