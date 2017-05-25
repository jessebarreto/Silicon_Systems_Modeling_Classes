/*
 * - master.h
 * 
 * 
 * Created by José Adalberto F. Gualeve  on 07/07/15.
 * Copyright 2015 - All rights reserved 
 */
#ifndef master_h
#define master_h

#include "systemc.h"
#include "noc_common.h"

SC_MODULE(Master)
{
    sc_fifo_out< flit_t >
        wr_data_port,
        addr_port;
    sc_fifo_out<sc_uint<16> >
        cmd_port;
    
    sc_fifo_in< flit_t >
        rd_data_port;
    sc_fifo_in<sc_uint<8> >
        wr_resp_port;

    SC_HAS_PROCESS(Master);
// constructor
  Master(sc_module_name _name, unsigned int identify) :
    sc_module(_name),
        identify(identify)
        {
            SC_THREAD(test_master);
            
        }
    void test_master();
  private:
    unsigned int identify;
    
    
};

void Master::test_master() 
{
    flit_t data, address;

    address = 0x00000100;
    switch (identify) {
        case  0:
          
            cout << "[Master0]: will send 1st value for writing"<<endl<<endl;
    
            data = 0x00000010;
            passo("m0",0);
            
            wr_data_port.write( data );
            passo("m0,wr_data_port.write",1);
            cmd_port.write( CMD_SW ); // store word
            passo("m0,cmd_port.write",1);
            addr_port.write( address );
            passo("m0,addr_port.write",1);
            if ( wr_resp_port.read() == 1 )
                cout << "[Master0]: Write OK" << endl;
            else
                cout << "[Master0]: Write error" << endl;
        
            passo("m0,wr_resp_port.read",2);
            cout <<"[Master0]: will send 2nd value for writing"<<endl<<endl;
            data = 0x00000020;
            address+=4;
            wr_data_port.write( data );
            cmd_port.write( CMD_SW ); // store word
            addr_port.write( address );
        
            if ( wr_resp_port.read() == 1 )
                cout << "[Master0]: Write OK" << endl;
            else
                cout << "[Master0]: Write error" << endl;
            break;
            
        case 1:
            
            cout <<"[Master1]: will read a value from memory"<<endl<<endl;
            cmd_port->write( CMD_LW );
            addr_port->write( address );
            data = rd_data_port->read();
    
            cout << "[Master1]: Result = " << data << endl;
            break;
            
    }

}


#endif
