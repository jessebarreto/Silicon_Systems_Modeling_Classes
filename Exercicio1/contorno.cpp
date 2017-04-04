/*
 *  contorno.cpp
 *  fa_sc
 *
 *  Created by Ricardo Jacobi on 2/4/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "contorno.h"

void contorno::aciona() {
	cout << "---" << "   X " << " Y " << "v " << "V" << " S" << endl;
	x = 0; y = 0; vem = 0;
	wait(1, SC_PS);
	cout << sc_time_stamp() << " " << x << " " << y << " " << vem << " " << vai << " " << soma << endl;
	x = 0; y = 0; vem = 1;
	wait(1, SC_PS);
	cout << sc_time_stamp() << " " << x << " " << y << " " << vem << " " << vai << " " << soma << endl;
	x = 0; y = 1; vem = 0;
	wait(1, SC_PS);
	cout << sc_time_stamp() << " " << x << " " << y << " " << vem << " " << vai << " " << soma << endl;
	x = 0; y = 1; vem = 1;
	wait(1, SC_PS);
	cout << sc_time_stamp() << " " << x << " " << y << " " << vem << " " << vai << " " << soma << endl;
	x = 1; y = 0; vem = 0;
	wait(1, SC_PS);
	cout << sc_time_stamp() << " " << x << " " << y << " " << vem << " " << vai << " " << soma << endl;
	x = 1; y = 0; vem = 1;
	wait(1, SC_PS);
	cout << sc_time_stamp() << " " << x << " " << y << " " << vem << " " << vai << " " << soma << endl;
	x = 1; y = 1; vem = 0;
	wait(1, SC_PS);
	cout << sc_time_stamp() << " " << x << " " << y << " " << vem << " " << vai << " " << soma << endl;
	x = 1; y = 1; vem = 1;
	wait(1, SC_PS);		
	cout << sc_time_stamp() << " " << x << " " << y << " " << vem << " " << vai << " " << soma << endl;
}
