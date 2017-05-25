/*
 * Decod.h
 *
 *  Created on: 09/07/2015
 *   *  Modified by José Adalberto F. Gualeve on 30/04/16
 *      Author: soudre
 */

#ifndef DECOD_H
#define DECOD_H
#include <systemc.h>

SC_MODULE(Decod) {

	//Entrada e saida do modulo de decodificacao:(recebe o flit do roteamento e o desempacota, entregando ao modulo de destino)

	sc_fifo_in<sc_uint<53> > i_decod;
	sc_fifo_out<sc_uint<32> > o_decod;

	SC_HAS_PROCESS(Decod);

		Decod(sc_module_name n) :
				sc_module(n) {
			SC_THREAD(lerDecod);
			SC_THREAD(main);
		}

		void lerDecod();
		void main();



	private:

		bool eh_decod;

		sc_uint<53> dado_decod;

		sc_event dado_decod_evt, main_ack2_evt;


	};
#endif
