#ifndef PROJECT_BASE_V1_1_PERIODICTHREAD_HPP
#define PROJECT_BASE_V1_1_PERIODICTHREAD_HPP
#include "../lib/hw.h"
#include "tcb.hpp"
#include "../h/syscall_c.hpp"
class PeriodicThread: public TCB{

public:
    void terminate();
    virtual bool isPeriodic() const override {return true;}
    static PeriodicThread* createPeriodicThread(Body body, void* arg);
protected:
    using TCB::TCB;
    PeriodicThread(time_t period,Body body, uint64 timeSlice, void* arg):TCB(body,timeSlice,arg),period(period){}
    void periodicActivation();
private:
    time_t period;
public:
    time_t getPeriod() const;

    void setPeriod(time_t period);

    static PeriodicThread** arrayPeriodic;
    static int i;

    void incrasePeriodicCOunter();
    void addToPeriodicArray(PeriodicThread *thread);

};


#endif
