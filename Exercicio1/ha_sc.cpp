/*
 *  ha_sc.cpp
 *  fa_sc
 *
 *  Created by Ricardo Jacobi on 1/28/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "systemc.h"

using namespace std;

SC_MODULE (ha_sc) {
	
	sc_in<bool> x, y;
	sc_out<bool> s, v;
	
	
	SC_CTOR(ha_sc) {
		SC_METHOD(proc);
		sensitive << x << y;
	}
	
	void proc(void) {
		s = x ^ y;
		v = x & y;
	}
};

