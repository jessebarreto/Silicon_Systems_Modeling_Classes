
#include "ula32.h"
#include "ula32tb.h"


int sc_main(int argc, char *argv[])
{
    Ula32 ula("ULA");
    Ula32Tb ulatb("ULATB");

    sc_signal<int32_t> a, b;
    sc_signal<int8_t> control;
    sc_signal<int32_t> z;
    sc_signal<bool> zero;


    ula.a(a);               ulatb.a(a);
    ula.b(b);               ulatb.b(b);
    ula.control(control);   ulatb.control(control);
    ula.z(z);               ulatb.z(z);
    ula.zero(zero);         ulatb.zero(zero);

    sc_trace_file *wf = sc_create_vcd_trace_file("ULA32_Traces");
    sc_trace(wf, ulatb.a, "A");
    sc_trace(wf, ulatb.b, "B");
    sc_trace(wf, ulatb.control, "CONTROL");
    sc_trace(wf, ulatb.z, "Z");
    sc_trace(wf, ulatb.zero, "ZERO");

    sc_start();
    sc_close_vcd_trace_file(wf);

    return 0;
}
