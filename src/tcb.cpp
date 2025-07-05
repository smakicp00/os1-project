#include "../h/tcb.hpp"
#include "../h/riscv.hpp"
#include "../h/PeriodicThread.hpp"
#include "../h/print.hpp"
TCB *TCB::running = nullptr;

uint64 TCB::timeSliceCounter = 0;

TCB *TCB::createThread(Body body, void* arg)
{
    return new TCB(body, TIME_SLICE, arg);
}

void TCB::yield()
{
    __asm__ volatile ("ecall");
}

void TCB::dispatch()
{
    TCB *old = running;
    if (!old->isFinished()) { Scheduler::put(old); }
    running = Scheduler::get();

//    while(running->isPeriodic()){
//        PeriodicThread *tmp = (PeriodicThread*)running;
//        int period = tmp->getPeriod();
//        if(period > 0){
//            period-=1;
//            tmp->setPeriod(period);
//            TCB*old = running;
//            Scheduler::put(old);
//            running = Scheduler:: get();
//        }
//        else{
//            break;
//        }
//    }

    TCB::contextSwitch(&old->context, &running->context);
}

void TCB::threadWrapper()
{
    Riscv::popSppSpie();
    running->body(running->arg);
    running->setFinished(true);
    TCB::yield();
}
