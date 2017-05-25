/*
 * - kernel_ni.cpp
 * 
* 
 * Created by José Adalberto F. Gualeve  on 08/07/15.
 * Copyright 2015 - All rights reserved 
*/

#include "systemc.h"
#include "kernel_ni.h"
#include "bitset"

flit1_4t KernelNetInterface::identify_tab( flit_t address ) 
{
    if ( address < 0x00010000 ) 
        return 2;                    // memory 2 (slave) (0 .. 64k-1)
    else if (address < 0x00100000 ) 
        return 3;                    // memory 3 (slave) (64k .. 1M-1)
    else if (address < 0x00100000 ) 
        return 4;                    // memory 4 (slave) (1M .. 2M-1 )
    else if (address < 0xFFFFF800 ) 
        return 5;                    // memory 5 (slave) (2M .. ~4G )
    else if (address < 0xFFFFFC00 ) 
        return 0;                    // cpu 0 (master) (512 bytes)
    else 
        return 1;                    // cpu 1 (master) (512 bytes + altos)
}

void KernelNetInterface::packetMaker() 
{
    int i;
    flit_t data;

    cout << "["<< this->name() << "::packetMaker()] kernel id: " << identify << endl;
        
    for (;;) {
        
        data = bufferPM_port.read(); // read 1st flit (cmd + flgs or SDCmd)
        queueOut[0] = data; // transfer command to queueOut[0] LSBs
        if ( identify < 2 ) { // 128..255 = masters, 
            queueOut[0].range(flit_size-1, flit_size-8) = identify;                   // source identify
            data = bufferPM_port.read(); // read 2nd flit (address in master mode)
            queueOut[0].range(flit_size-9, flit_size-16) = identify_tab( data ); // target identify
        }
        else {
            data = bufferPM_port.read(); // read 2nd flit (data in slave mode)
        }
        
        queueOut[1] = data;
        for (i = 2; i < (pkg_size); i++) { // read next flits
            queueOut[i] = bufferPM_port.read();
        }            
        
        for (i = 0; i < pkg_size; i++) {
            out.write(queueOut[i]);
            cout << "[" << this->name() << "::packetMaker]:<<<flit"<<i<<" sent: [" << std::hex << (queueOut[i])<< std::dec<<"]"<<endl;
                
        }
        
    }
        
}
    

void KernelNetInterface::packetDisassembly() 
{
    int i;
    flit1_4t id;
    
    
    for (;;) {
        for (i=0; i< pkg_size; i++) {
            
            queueIn[i] = in.read();
            cout << "["<< this->name() << "::packetDisassembly]: >>>flit"<<i<<" received: [" << std::hex<<queueIn[i]<<std::dec<<"]"<<endl;
            
        }
        
        for (i=0; i<pkg_size; i++) {
            bufferPD_port.write(queueIn[i]);
        }
        
    }
        
}
