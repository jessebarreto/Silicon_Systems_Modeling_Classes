/*
 * - main.cpp
 * 
 * 
 * Created by José Adalberto F. Gualeve  and Marlon Soudre on 07/07/15.
 * Modified by José Adalberto F. Gualeve on 05/05/16
 * Copyright 2015,2016 - All rights reserved 
 */

#include "systemc.h"
#include "noc_common.h"
#include "kernel_ni.h"
#include "shell_master_ni.h"
#include "shell_slave_ni.h"
#include "master.h"
#include "slave.h"
#include "router.h"
#include "cod.h"
#include "decod.h"
#include <iostream>

using namespace std;

/*
         [ni00]  ||            [ni01]  ||
              \\ ||                 \\ || 
           ====(r00)===r0001/r0100===(r01)=
                 ||                    ||       
             r0010/r1000           r0111/r1101
                 ||                    ||         
         [ni10]  ||            [ni11]  ||     
              \\ ||                 \\ ||   
           ====(r10)===r1011/r1110===(r11)==
                 ||                    ||         
             r1020/r2010           r1121/r2111 
                 ||                    ||   
         [ni20]  ||            [ni21]  ||   
              \\ ||                 \\ ||    
           ====(r20)===r2021/r2120===(r21)===
                 ||                    ||
         
*/

int sc_main ( int argc, char *argv[]) {
    
    Master master0("master0",0);
    Master master1("master1",1);
    Slave slave2("slave2",2);   
    Slave slave3("slave3",3); 
    Slave slave4("slave4",4); 
    Slave slave5("slave5",5);
    
    KernelNetInterface m0_kernel("m0_kernel", 0);
    KernelNetInterface m1_kernel("m1_kernel", 1);
    KernelNetInterface s2_kernel("s2_kernel", 2);
    KernelNetInterface s3_kernel("s3_kernel", 3);
    KernelNetInterface s4_kernel("s4_kernel", 4);
    KernelNetInterface s5_kernel("s5_kernel", 5);
    ShellMasterInterface m0_shell("m0_shell", 0);
    ShellMasterInterface m1_shell("m1_shell", 1);
    ShellSlaveInterface s2_shell("s2_shell", 2);
    ShellSlaveInterface s3_shell("s3_shell", 3);
    ShellSlaveInterface s4_shell("s4_shell", 4);
    ShellSlaveInterface s5_shell("s5_shell", 5);

    Cod cod00("cod00"), cod01("cod01"),
        cod10("cod10"), cod11("cod11"),
        cod20("cod20"), cod21("cod21");

    Decod decod00("decod00"), decod01("decod01"),
        decod10("decod10"), decod11("decod11"),
        decod20("decod20"), decod21("decod21");

    Router r00("r00"),  r01("r01"),
	r10("r10"),  r11("r11"),
        r20("r20"),  r21("r21");

    sc_fifo<sc_uint<53> >

             /*
             * Channels: out border
             **/        
	// i_oeste_0("i_oeste_0",1), o_oeste_0("o_oeste_0",1), i_oeste_1("i_oeste_1",1),
	// o_oeste_1("o_oeste_1",1), i_oeste_2("i_oeste_2",1), o_oeste_2("o_oeste_2",1),
	 i_norte_0("i_norte_0",1), o_norte_0("o_norte_0",1), i_norte_1("i_norte_1",1), o_norte_1("o_norte_1",1),
	// i_leste_0("i_leste_0",1), o_leste_0("o_leste_0",1), i_leste_1("i_leste_1",1),
	// o_leste_1("o_leste_1",1), i_leste_2("i_leste_2",1), o_leste_2("o_leste_2",1),
	 i_sul_0("i_sul_0",1), o_sul_0("o_sul_0",1), i_sul_1("i_sul_2",1), o_sul_1("o_sul_2",1),

            /*
             * Channels: router .. router
             **/ 
        c0001("c0001",1), c0100("c0100",1),
        c0010("c0010",1), c1000("c1000",1), c0111("c0111",1), c1101("c1101",1),
        c1011("c1011",1), c1110("c1110",1),
        c1020("c1020",1), c2010("c2010",1), c1121("c1121",1), c2111("c2111",1),
        c2021("c2021",1), c2120("c2120",1);
            /*
         * Channels: routers .. cod/decod
         **/ 
    sc_fifo<sc_uint<53> > // router to decod
        r2d00("r2d00",8), r2d10("r2d10",8), r2d20("r2d20",8),
        r2d01("r2d01",8), r2d11("r2d11",8), r2d21("r2d21",8);
        
    sc_fifo<sc_uint<53> > // cod to router
        c2r00("c2r00",8), c2r10("c2r10",8), c2r20("c2r20",8),
        c2r01("c2r01",8), c2r11("c2r11",8), c2r21("c2r21",8);
    
        /*
         * Channels: routers .. NI(kernel)
         **/ 
    sc_fifo< flit_t > // NI to cod
        k2c00("k2c00",8), k2c10("k2c10",8), k2c20("k2c20",8),
        k2c01("k2c01",8), k2c11("k2c11",8), k2c21("k2c21",8);
        
    sc_fifo< flit_t > // decod to NI
        d2k00("d2k00",8), d2k10("d2k10",8), d2k20("d2k20",8),
        d2k01("d2k01",8), d2k11("d2k11",8), d2k21("d2k21",8);
    
        /*
         * Channels: IP-Cores .. NI(shell)
         **/ 
    sc_fifo< flit_t > 
        wr_data0("wr_data0",1), wr_data1("wr_data1",1), wr_data2("wr_data2",1),
        wr_data3("wr_data3",1), wr_data4("wr_data4",1), wr_data5("wr_data5",1),
        addr0("addr0",1), addr1("addr1",1), addr2("addr2",1),
        addr3("addr3",1), addr4("addr4",1), addr5("addr5",1),
        rd_data0("rd_data0",1), rd_data1("rd_data1",1), rd_data2("rd_data2",1),
        rd_data3("rd_data3",1), rd_data4("rd_data4",1), rd_data5("rd_data5",1);
    sc_fifo< flit1_2t>
        cmd0("cmd0",1), cmd1("cmd1",1), cmd2("cmd2",1),
        cmd3("cmd3",1), cmd4("cmd4",1), cmd5("cmd5",1);
    sc_fifo< flit1_4t>
        wr_resp0("wr_resp0",1), wr_resp1("wr_resp1",1), wr_resp2("wr_resp2",1),
        wr_resp3("wr_resp3",1), wr_resp4("wr_resp4",1), wr_resp5("wr_resp5",1);

        /*
         * Channels: NI(shell) .. NI(kernel)
         **/ 
    sc_fifo< flit_t > 
        bufferPM0("bufferPM0",1), bufferPM1("bufferPM1",1), bufferPM2("bufferPM2",1),
        bufferPM3("bufferPM3",1), bufferPM4("bufferPM4",1), bufferPM5("bufferPM5",1),
        bufferPD0("bufferPD0",1), bufferPD1("bufferPD1",1), bufferPD2("bufferPD2",1),
        bufferPD3("bufferPD3",1), bufferPD4("bufferPD4",1), bufferPD5("bufferPD5",1);


        // router r00
    r00.i_oeste(c2r00); r00.o_oeste(r2d00);
    r00.i_norte(i_norte_0); r00.o_norte(o_norte_0);
    r00.i_leste(c0100); r00.o_leste(c0001);
    r00.i_sul(c1000); r00.o_sul(c0010);
    
        // router r01
    r01.i_oeste(c0001); r01.o_oeste(c0100);
    r01.i_norte(i_norte_1); r01.o_norte(o_norte_1);
    r01.i_leste(c2r01); r01.o_leste(r2d01);
    r01.i_sul(c1101); r01.o_sul(c0111);

        // router r10
    r10.i_oeste(c2r10); r10.o_oeste(r2d10);
    r10.i_norte(c0010); r10.o_norte(c1000);
    r10.i_leste(c1110); r10.o_leste(c1011);
    r10.i_sul(  c2010); r10.o_sul(  c1020);

        // router r11
    r11.i_oeste(c1011); r11.o_oeste(c1110);
    r11.i_norte(c0111); r11.o_norte(c1101);
    r11.i_leste(c2r11); r11.o_leste(r2d11);
    r11.i_sul(c2111); r11.o_sul(c1121);

        // router r20
    r20.i_oeste(c2r20); r20.o_oeste(r2d20);
    r20.i_norte(c1020); r20.o_norte(c2010);
    r20.i_leste(c2120); r20.o_leste(c2021);
    r20.i_sul(i_sul_0); r20.o_sul(o_sul_0);

        // router r21
    r21.i_oeste(c2021); r21.o_oeste(c2120);
    r21.i_norte(c1121); r21.o_norte(c2111);
    r21.i_leste(c2r21); r21.o_leste(r2d21);
    r21.i_sul(i_sul_1); r21.o_sul(o_sul_1);

    cod00.i_cod(k2c00);
    cod00.o_cod(c2r00);
    cod10.i_cod(k2c10);
    cod10.o_cod(c2r10);
    cod20.i_cod(k2c20);
    cod20.o_cod(c2r20);
    cod01.i_cod(k2c01);
    cod01.o_cod(c2r01);
    cod11.i_cod(k2c11);
    cod11.o_cod(c2r11);
    cod21.i_cod(k2c21);
    cod21.o_cod(c2r21);

    decod00.i_decod(r2d00);
    decod00.o_decod(d2k00);
    decod10.i_decod(r2d10);
    decod10.o_decod(d2k10);
    decod20.i_decod(r2d20);
    decod20.o_decod(d2k20);
    decod01.i_decod(r2d01);
    decod01.o_decod(d2k01);
    decod11.i_decod(r2d11);
    decod11.o_decod(d2k11);
    decod21.i_decod(r2d21);
    decod21.o_decod(d2k21);

    master0.wr_data_port(wr_data0);  m0_shell.wr_data_port(wr_data0);
    master1.wr_data_port(wr_data1);  m1_shell.wr_data_port(wr_data1);
    master0.cmd_port(cmd0);          m0_shell.cmd_port(cmd0);
    master1.cmd_port(cmd1);          m1_shell.cmd_port(cmd1);
    master0.addr_port(addr0);        m0_shell.addr_port(addr0);
    master1.addr_port(addr1);        m1_shell.addr_port(addr1);
    master0.rd_data_port(rd_data0);  m0_shell.rd_data_port(rd_data0);
    master1.rd_data_port(rd_data1);  m1_shell.rd_data_port(rd_data1);
    master0.wr_resp_port(wr_resp0);  m0_shell.wr_resp_port(wr_resp0);
    master1.wr_resp_port(wr_resp1);  m1_shell.wr_resp_port(wr_resp1);

    m0_shell.bufferPD_port(bufferPD0); m0_kernel.bufferPD_port(bufferPD0);
    m1_shell.bufferPD_port(bufferPD1); m1_kernel.bufferPD_port(bufferPD1);
    m0_shell.bufferPM_port(bufferPM0); m0_kernel.bufferPM_port(bufferPM0);
    m1_shell.bufferPM_port(bufferPM1); m1_kernel.bufferPM_port(bufferPM1);

    m0_kernel.out(k2c00); m0_kernel.in(d2k00);
    m1_kernel.out(k2c10); m1_kernel.in(d2k10);    
    s2_kernel.out(k2c20); s2_kernel.in(d2k20);    
    s3_kernel.out(k2c01); s3_kernel.in(d2k01);    
    s4_kernel.out(k2c11); s4_kernel.in(d2k11);    
    s5_kernel.out(k2c21); s5_kernel.in(d2k21);
    
    s2_shell.bufferPD_port(bufferPD2); s2_kernel.bufferPD_port(bufferPD2);
    s3_shell.bufferPD_port(bufferPD3); s3_kernel.bufferPD_port(bufferPD3);
    s4_shell.bufferPD_port(bufferPD4); s4_kernel.bufferPD_port(bufferPD4);
    s5_shell.bufferPD_port(bufferPD5); s5_kernel.bufferPD_port(bufferPD5);
    s2_shell.bufferPM_port(bufferPM2); s2_kernel.bufferPM_port(bufferPM2);
    s3_shell.bufferPM_port(bufferPM3); s3_kernel.bufferPM_port(bufferPM3);
    s4_shell.bufferPM_port(bufferPM4); s4_kernel.bufferPM_port(bufferPM4);
    s5_shell.bufferPM_port(bufferPM5); s5_kernel.bufferPM_port(bufferPM5);

    slave2.wr_data_port(wr_data2);  s2_shell.wr_data_port(wr_data2);
    slave3.wr_data_port(wr_data3);  s3_shell.wr_data_port(wr_data3);
    slave4.wr_data_port(wr_data4);  s4_shell.wr_data_port(wr_data4);
    slave5.wr_data_port(wr_data5);  s5_shell.wr_data_port(wr_data5);
    slave2.cmd_port(cmd2);          s2_shell.cmd_port(cmd2);
    slave3.cmd_port(cmd3);          s3_shell.cmd_port(cmd3);
    slave4.cmd_port(cmd4);          s4_shell.cmd_port(cmd4);
    slave5.cmd_port(cmd5);          s5_shell.cmd_port(cmd5);
    slave2.addr_port(addr2);        s2_shell.addr_port(addr2);
    slave3.addr_port(addr3);        s3_shell.addr_port(addr3);
    slave4.addr_port(addr4);        s4_shell.addr_port(addr4);
    slave5.addr_port(addr5);        s5_shell.addr_port(addr5);
    slave2.rd_data_port(rd_data2);  s2_shell.rd_data_port(rd_data2);
    slave3.rd_data_port(rd_data3);  s3_shell.rd_data_port(rd_data3);
    slave4.rd_data_port(rd_data4);  s4_shell.rd_data_port(rd_data4);
    slave5.rd_data_port(rd_data5);  s5_shell.rd_data_port(rd_data5);
    slave2.wr_resp_port(wr_resp2);  s2_shell.wr_resp_port(wr_resp2);
    slave3.wr_resp_port(wr_resp3);  s3_shell.wr_resp_port(wr_resp3);
    slave4.wr_resp_port(wr_resp4);  s4_shell.wr_resp_port(wr_resp4);
    slave5.wr_resp_port(wr_resp5);  s5_shell.wr_resp_port(wr_resp5);    

    sc_start();
    
    return 0;
}

