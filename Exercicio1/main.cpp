
#include "contorno.h"
#include "fa.cpp"
#include <iostream>

using namespace std;

int sc_main (int argc, char *argv[]) {
    sc_signal<bool> x, y, vem, soma, vai;
	
	sc_trace_file* trace_file = sc_create_vcd_trace_file("wave");
	
	sc_trace(trace_file, x, "x");
	sc_trace(trace_file, y, "y");
	sc_trace(trace_file, vem, "vem");
	sc_trace(trace_file, soma, "soma");
	sc_trace(trace_file, vai, "vai");
	
	cout << "iniciando ... " << endl;
		
	fa f("f");
	contorno c("c");
	
	f.x(x);
	f.y(y);
	f.vem(vem);
	f.soma(soma);
	f.vai(vai);
	
	c.x(x);
	c.y(y);
	c.vem(vem);
	c.soma(soma);
	c.vai(vai);
			
    sc_start (100, SC_PS);
	
	sc_close_vcd_trace_file(trace_file);
	cout << "Criou wave.vcd" << endl;
	
    return 0;
	
}
