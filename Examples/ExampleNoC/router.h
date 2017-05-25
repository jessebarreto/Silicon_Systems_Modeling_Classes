/*
 *  router.h
 *  roteador
 *
 *  Created by Ricardo Jacobi on 27/5/15.
 *  Copyright 2015 Universidade de Brasilia. All rights reserved.
 *
 */

#ifndef ROUTER_H
#define ROUTER_H

#include <systemc.h>

SC_MODULE(Router) {

	//Entradas e saidas do modulo de roteamento
	sc_fifo_in<sc_uint<53> > i_norte, i_oeste, i_sul, i_leste;
	sc_fifo_out<sc_uint<53> > o_sul, o_leste, o_oeste, o_norte;


	SC_HAS_PROCESS(Router);
	
	Router(sc_module_name n) : 
			sc_module(n) {
		SC_THREAD(lerOeste);
		SC_THREAD(lerSul);
		SC_THREAD(lerLeste);
		SC_THREAD(lerNorte);
		SC_THREAD(main);
	}
	
	void lerOeste();
	void lerSul();
	void lerLeste();
	void lerNorte();
	void main();
	


private:

	sc_event dado_oeste_evt, dado_norte_evt, dado_sul_evt, dado_leste_evt, main_ack_evt;

	sc_uint<53> dado_oeste, dado_norte, dado_sul, dado_leste;

	bool eh_oeste, eh_norte, eh_sul, eh_leste;

	int x, y, ent, said, saida;

};

#endif
