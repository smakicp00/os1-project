#include "../h/syscall_c.hpp"
#include "../h/PeriodicThread.hpp"
#include "../h/tcb.hpp"
int thread_create(thread_t *handle, void (*start_routine)(void *), void *arg) {
    *handle = TCB::createThread(start_routine,arg);
    return 1;
}
int thread_Pcreate(thread_t *handle, void (*start_routine)(void *), void *arg) {
    *handle = PeriodicThread::createPeriodicThread(start_routine,arg);
    return 1;
}

int sem_open(sem_t *handle, unsigned init) {
    *handle = new Semaphore(init);
    return 0;
}

int sem_wait(sem_t id) {
    id->wait();
    return 0;
}

int sem_signal(sem_t id) {
    id->signal();
    return 0;
}
void putc(char c){
    int a = 1;
    //uint64 x = (uint64)c;
    __asm__ volatile ("mv a0, %0":: "r"(a): "a0");
    __asm__ volatile ("mv a1, %0":: "r"(c): "a1");
    __asm__ volatile ("ecall");
    //asm volatile ("mv %0, a0": "=r"(a)::);

}
int time_sleep (time_t t){
    if(TCB::running->isPeriodic()){
        PeriodicThread *tmp = (PeriodicThread*)TCB::running;
        tmp->setPeriod(t);
    }
    return 1;
}

int time_sleep_ispravno (time_t t){
    int a = 10;

    __asm__ volatile ("mv a0, %0":: "r"(a): "a0");
    __asm__ volatile ("mv a1, %0":: "r"(t): "a1");
    __asm__ volatile ("ecall");
    return 1;
}