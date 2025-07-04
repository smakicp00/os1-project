#ifndef PROJECT_BASE_V1_1_SEMAPHORE_HPP
#define PROJECT_BASE_V1_1_SEMAPHORE_HPP
#include "../lib/hw.h"
#include "list.hpp"
#include "tcb.hpp"
class TCB;

class Semaphore {

public:

    Semaphore(uint64 val):val(val){}
    void wait();
    void signal();
    static Semaphore *sem;

protected:

    void unblock();
    void block();

private:
    int val;
    List<TCB> suspendedQueue;
};


#endif
