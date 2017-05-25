/*
 * - slave.h
 * 
 * 
 * Created by José Adalberto F. Gualeve  on 07/07/15.
 * Copyright 2015 - All rights reserved 
 */
#ifndef slave_h
#define slave_h
#include "systemc.h"
#include "noc_common.h"


SC_MODULE ( Slave ) {

    sc_fifo_in< flit_t >
        wr_data_port,
        addr_port;
    sc_fifo_in< flit1_2t >
        cmd_port;
    
    sc_fifo_out< flit_t >
        rd_data_port;
    sc_fifo_out< flit1_4t >
        wr_resp_port;

    SC_HAS_PROCESS(Slave);
// constructor
  Slave(sc_module_name _name, unsigned int identify) :
    sc_module(_name),
        identify(identify)
        {
            SC_THREAD(test_slave);

            MEM = new int [mem_size];
            for (unsigned int i=0; i < mem_size; i++)
                MEM[i]=0;
            
        }
    void test_slave();
  private:
    unsigned int identify;
    int *MEM;
        
};

void Slave::test_slave() 
{
    flit_t data, address;
    flit1_2t cmd;
        
    for(;;) {
        address = addr_port.read();
        if ( ( cmd = cmd_port.read() ) & 8 ) { // CMD_SB, CMD_SH or CMD_SW
            
            cout << "[" << this->name() << "]: writing value"<<endl<<endl;
            MEM[address] = wr_data_port.read();
            cout << "[" << this->name() << "]: Value: "<< MEM[address]<< " written at address: "<< address << endl;
            
            wr_resp_port.write(1);
        }
        else { // CMD_LB, CMD_LH or CMD_LW
//            data = wr_data_port.read();
            
            cout << "[" << this->name() << "]: reading value..."<<endl<<endl;
            rd_data_port.write( MEM[address] );
            cout << "[" << this->name() << "]: Value: "<< MEM[address]<< " read from address: "<< address << endl;
        }
/*        for ( unsigned int i=3; i<pkg_size; i++) {            
            data = wr_data_port.read();
            }*/
        
    }
}

#endif
