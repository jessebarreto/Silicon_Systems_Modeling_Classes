/*
 * - shell_slave_ni.h
 * 
* 
 * Created by José Adalberto F. Gualeve  on 13/07/15.
 * Copyright 2015 - All rights reserved 
*/
#ifndef shell_slave_ni_h
#define shell_slave_ni_h

#include "systemc.h"

#include "bitset"

SC_MODULE ( ShellSlaveInterface ) {
        // to slave ports
    sc_fifo_out< flit_t >
        wr_data_port,
        addr_port;
    sc_fifo_out< flit1_2t >
        cmd_port;
    
    sc_fifo_in< flit_t >
        rd_data_port;
    sc_fifo_in< flit1_4t >
        wr_resp_port;
    
        // to kernel ports
    sc_fifo_out < flit_t > bufferPM_port;
    sc_fifo_in  < flit_t > bufferPD_port;
    
    void proc();
    
    SC_HAS_PROCESS( ShellSlaveInterface );
    ShellSlaveInterface (
        sc_module_name _name,
        flit1_4t identify
                          ):
    sc_module(_name), identify(identify) 
    {
        SC_THREAD(proc);
    }
  private:
    flit1_4t identify;
        
};

void ShellSlaveInterface::proc() 
{
    flit_t sdcmd, data, address, nulo; // sdcmd = source+dest+command
    flit1_4t tmp;
    
    for(;;) {
        
        sdcmd = bufferPD_port.read();
        address = bufferPD_port.read();
        data  = bufferPD_port.read();
        for (unsigned int i=3; i<pkg_size; i++)
            nulo = bufferPD_port.read();
        
        
        if ( sdcmd & 8 )  { // CMD_SB, CMD_SH or CMD_SW
            wr_data_port.write(data);
        }
        
        addr_port.write(address);
        cmd_port.write(sdcmd.range(15,0));

        data = ( (sdcmd & 8) ? (flit_t)wr_resp_port.read() : rd_data_port.read() );

        cout << "data read from slave: " << data << endl;
        
            // inverter source / dest para retornar
        cout << "SDCMD original " << std::bitset<32>(sdcmd) << endl;
        
        tmp = sdcmd.range(31,24);
        sdcmd.range(31,24) = sdcmd.range(23,16);
        sdcmd.range(23,16) = tmp;
        cout << "SDCMD alterado " << std::bitset<32>(sdcmd) << endl;

        bufferPM_port.write(sdcmd);
//        bufferPM_port.write(address);  // descomentar se o kernel não diferenciar entre slave e master
        bufferPM_port.write(data);
        for (unsigned int i=2; i< pkg_size; i++)
            bufferPM_port.write(0);
        
    }
    
}

#endif
