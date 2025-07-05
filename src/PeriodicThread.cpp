#include "../h/PeriodicThread.hpp"
#include "../lib/console.h"

int PeriodicThread:: i = 0;

PeriodicThread** PeriodicThread::arrayPeriodic;

void PeriodicThread::periodicActivation() {}

void PeriodicThread::terminate() {}

PeriodicThread* PeriodicThread::createPeriodicThread(TCB::Body body, void *arg) {
    return new PeriodicThread(0,body, 2, nullptr);
}

time_t PeriodicThread::getPeriod() const {
    return period;
}

void PeriodicThread::setPeriod(time_t period) {
    PeriodicThread::period = period;
}

void PeriodicThread::incrasePeriodicCOunter() {
    PeriodicThread::i++;
}

void PeriodicThread::addToPeriodicArray(PeriodicThread *thread) {
    PeriodicThread::arrayPeriodic[i] = thread;
}

