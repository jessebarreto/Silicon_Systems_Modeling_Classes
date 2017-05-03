#include <systemc.h>

#ifndef GASSTATION_H
#define GASSTATION_H

SC_MODULE(GasStation)
{
    const sc_time TEMP_MIN;

    bool attendantFilling;

    double full1, full2;
    double fillTime;

    double tank1, tank2;
    unsigned count1, count2, maxCount;

    sc_event filled;

    sc_event customer1Request, customer2Request;
    sc_event fullTank;

    void attendantMethod();

    void customer1Thread();

    void customer2Thread();


    GasStation(sc_module_name name,
               double full1 = 10,
               double full2 = 11.1,
               double fillTime = 1.8,
               unsigned maxCount = 5) :
        sc_module(name),
        full1(full1),
        full2(full2),
        fillTime(fillTime),
        tank1(full1),
        tank2(full1),
        count1(0),
        count2(0),
        maxCount(maxCount),
        attendantFilling(false)
    {
//        SC_METHOD(customer1Thread);
//        sensitive(filled);

//        SC_THREAD(customer2Thread);

//        SC_METHOD(attendantMethod);
//        sensitive << customer1Request << customer2Request;
//        dont_initialize();
    }
};

extern unsigned errors;

void GasStation::attendantMethod()
{
//    for (;;) {
//        wait(fll)
//    }
}

void GasStation::customer1Thread()
{
//    for (;;)
//    {
//        wait(SC_ZERO_TIME);
//        std::cout << "Customer1 needs gas." << std::endl;

//    }
}

void GasStation::customer2Thread()
{

}

#endif // GASSTATION_H
