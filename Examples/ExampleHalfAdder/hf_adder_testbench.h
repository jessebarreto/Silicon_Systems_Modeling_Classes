
#include <systemc.h>

SC_MODULE(HalfAdderTb)
{
  sc_in<bool>  sum, carry_out;
  sc_out<bool> x, y;

  void acionar();

  SC_CTOR(HalfAdderTb)
  {
    SC_THREAD(acionar);
  }
};

void HalfAdderTb::acionar()
{
    std::cout << "-----" << "\tX" << "\tY" << "\tSUM" << "\tCARRYOUT" << std::endl;

    x = false; y = false;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << x << "\t" << y << "\t" << sum << "\t" << carry_out << std::endl;

    x = false; y = true;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << x << "\t" << y << "\t" << sum << "\t" << carry_out << std::endl;

    x = true; y = false;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << x << "\t" << y << "\t" << sum << "\t" << carry_out << std::endl;

    x = true; y = true;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << x << "\t" << y << "\t" << sum << "\t" << carry_out << std::endl;

    x = false; y = false;
    wait(5, SC_NS);
    std::cout << sc_time_stamp() << "\t" << x << "\t" << y << "\t" << sum << "\t" << carry_out << std::endl;
}
