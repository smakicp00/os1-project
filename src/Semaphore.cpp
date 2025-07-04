#include "../h/Semaphore.hpp"

Semaphore *Semaphore::sem = nullptr;

void Semaphore::signal() {
    if (++val <= 0)unblock();
}

void Semaphore::wait() {
    if (--val < 0)block();
}

void Semaphore::unblock() {
    if(suspendedQueue.peekLast()!= nullptr){TCB *tcb = suspendedQueue.removeLast();
    Scheduler::put(tcb);}
}

void Semaphore::block() {
    TCB *old = TCB::running;
    suspendedQueue.addFirst(old);

    TCB::running = Scheduler::get();

    TCB::contextSwitch(&old->context, &TCB::running->context);
}
