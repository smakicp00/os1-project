#include "../h/syscall_c.hpp"


int thread_create(thread_t *handle, void (*start_routine)(void *), void *arg) {
    *handle = TCB::createThread(start_routine,arg);
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

