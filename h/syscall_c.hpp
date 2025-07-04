#ifndef PROJECT_BASE_V1_1_SYSCALL_C_HPP
#define PROJECT_BASE_V1_1_SYSCALL_C_HPP
#include "../h/tcb.hpp"
#include "../h/Semaphore.hpp"

typedef TCB* thread_t;
int thread_create (
    thread_t* handle,
    void(*start_routine)(void*),
    void* arg
);

class Semaphore;
typedef Semaphore* sem_t;
int sem_open (
        sem_t* handle,
        unsigned init
);

int sem_wait (sem_t id);
int sem_signal (sem_t id);


#endif
