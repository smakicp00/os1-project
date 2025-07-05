#include "../h/tcb.hpp"
#include "../h/workers.hpp"
#include "../h/print.hpp"
#include "../h/riscv.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../h/syscall_c.hpp"
#include "../lib/console.h"
#include "../h/riscv.hpp"
#include "../h/PeriodicThread.hpp"
int main()
{

    MemoryAllocator::init();

    thread_t threads[5];


    sem_open(&Semaphore::sem, 3);

    thread_create(&threads[0], nullptr,nullptr);
    TCB::running = threads[0];


    threads[1] = PeriodicThread::createPeriodicThread(workerBodyA, nullptr);
    printString("ThreadA created\n");
    threads[2] = PeriodicThread::createPeriodicThread(workerBodyB, nullptr);
    printString("ThreadB created\n");
    threads[3] = PeriodicThread::createPeriodicThread(workerBodyC, nullptr);
    printString("ThreadC created\n");
    threads[4] = PeriodicThread::createPeriodicThread(workerBodyD, nullptr);
    printString("ThreadD created\n");

    //thread_create(&threads[1], workerBodyA,nullptr);
    //printString("ThreadA created\n");
//    thread_create(&threads[2], workerBodyB,nullptr);
//    printString("ThreadB created\n");
//    thread_create(&threads[3], workerBodyC,nullptr);
//    printString("ThreadC created\n");
//    thread_create(&threads[4], workerBodyD,nullptr);
//    printString("ThreadD created\n");

    Riscv::w_stvec((uint64) &Riscv::supervisorTrap); //Tabela prekidne rutine postavljena
    Riscv::ms_sstatus(Riscv::SSTATUS_SIE); //Omoguceni prekidi u S-modu

    while (!(threads[1]->isFinished() &&
             threads[2]->isFinished() &&
             threads[3]->isFinished() &&
             threads[4]->isFinished()))
    {
        TCB::yield();
    }



//    putc('X');

    for (auto &thread: threads)
    {
        delete thread;
    }
    printString("Finished\n");
    return 0;
}
