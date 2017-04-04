/*
 *  fa.cpp
 *  fa_sc
 *
 *  Created by Ricardo Jacobi on 1/28/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "ha_sc.cpp"

SC_MODULE (fa) {
	sc_in<bool> x, y, vem;
	sc_out<bool> soma, vai;
	
	
	ha_sc *h1, *h2;
	
	sc_signal<bool> s1, s2, s3;
	
	SC_CTOR (fa) {
		h1 = new ha_sc("h1");
		h2 = new ha_sc("h2");
		h1->x(x);
		h1->y(y);
		h1->s(s1);
		h1->v(s2);
		h2->x(s1);
		h2->y(vem);
		h2->s(soma);
		h2->v(s3);
		
		SC_METHOD(proc);
		sensitive << s2 << s3;
	}
	
	void proc() {
		vai = s2 | s3;
	}
};