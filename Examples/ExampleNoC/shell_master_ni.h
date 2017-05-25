/*
 * - shell_master_ni.h
 * 
* 
 * Created by José Adalberto F. Gualeve  on 13/07/15.
 * Copyright 2015 - All rights reserved 
*/
#ifndef shell_master_ni_h
#define shell_master_ni_h

#include "systemc.h"
#include "noc_common.h"
#include "bitset"

SC_MODULE ( ShellMasterInterface ) {
        // to/from master ports
    sc_fifo_in<flit_t >
        wr_data_port,
        addr_port;
    sc_fifo_in<flit1_2t >
        cmd_port;
    
    sc_fifo_out< flit_t >
        rd_data_port;
    sc_fifo_out< flit1_4t >
        wr_resp_port;
    
        // to/from kernel ports
    sc_fifo_out < flit_t > bufferPM_port;
    sc_fifo_in  < flit_t > bufferPD_port;

    void proc();
    
    SC_HAS_PROCESS( ShellMasterInterface );
    ShellMasterInterface (
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

void ShellMasterInterface::proc() 
{
    flit1_2t cmd;
    flit_t data, address, nulo;
    unsigned int i;
            
    for(;;) {
        
        data = 0;
            /*
             * send
             **/ 
        if ( ( cmd = cmd_port.read() ) & 8 )  // CMD_SB, CMD_SH or CMD_SW
            data = wr_data_port.read();
        cout << "["<< this->name() << "]: cmd read: " <<  std::hex << cmd << std::dec<<endl;
        
        address = addr_port.read();

        bufferPM_port.write(cmd);
        bufferPM_port.write(address);
        bufferPM_port.write(data);
        for (i=3; i<pkg_size; i++) 
            bufferPM_port.write(0);

            /*
             * receive
             **/ 
        
        cmd=bufferPD_port.read();
        data = bufferPD_port.read();
        cout << "sdcmd = " << std::bitset<16>(cmd)<< endl ;
        for (i=2; i<pkg_size; i++) 
            nulo=bufferPD_port.read();
        if ( cmd & 8 )
            wr_resp_port.write((flit1_4t)data);
        else
            rd_data_port.write(data);
    }
    
}

#endif
