#include "../h/tcb.hpp"
#include "../h/workers.hpp"
#include "../h/print.hpp"
#include "../h/riscv.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../h/syscall_c.hpp"
int main()
{

    MemoryAllocator::init();

    thread_t threads[5];


    sem_open(&Semaphore::sem, 3);

    thread_create(&threads[0], nullptr,nullptr);
    TCB::running = threads[0];

    thread_create(&threads[1], workerBodyA,nullptr);
    printString("ThreadA created\n");
    thread_create(&threads[2], workerBodyB,nullptr);
    printString("ThreadB created\n");
    thread_create(&threads[3], workerBodyC,nullptr);
    printString("ThreadC created\n");
    thread_create(&threads[4], workerBodyD,nullptr);
    printString("ThreadD created\n");

    Riscv::w_stvec((uint64) &Riscv::supervisorTrap); //Tabela prekidne rutine postavljena
    Riscv::ms_sstatus(Riscv::SSTATUS_SIE); //Omoguceni prekidi u S-modu

    for (int i = 0; i < 100000; ++i) {

    }

    while (!(threads[1]->isFinished() &&
             threads[2]->isFinished() &&
             threads[3]->isFinished() &&
             threads[4]->isFinished()))
    {
        TCB::yield();
    }

    for (auto &thread: threads)
    {
        delete thread;
    }
    printString("Finished\n");
    return 0;
}
