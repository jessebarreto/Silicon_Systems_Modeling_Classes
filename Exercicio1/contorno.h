/*
 *  contorno.h
 *  fa_sc
 *
 *  Created by Ricardo Jacobi on 2/4/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "systemc.h"

SC_MODULE (contorno) {
	
	sc_in<bool> vai, soma;
	sc_out<bool> x, y, vem;
	
	void aciona();
	
	SC_CTOR (contorno) {
		SC_THREAD(aciona);
	}
};

