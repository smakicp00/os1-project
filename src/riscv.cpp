#include "../h/riscv.hpp"
#include "../h/tcb.hpp"
#include "../lib/console.h"
#include "../lib/mem.h"
#include "../lib/hw.h"
#include "../h/MemoryAllocator.hpp"

void Riscv::popSppSpie() {
    __asm__ volatile("csrw sepc, ra");
    __asm__ volatile("sret");
}

void Riscv::handleSupervisorTrap() {
    uint64 scause = r_scause();
    int x = 0;

    if (scause == 0x0000000000000008UL || scause == 0x0000000000000009UL) {

        asm volatile ("mv %0, a0": "=r"(x)::);
        if (x == 1) {
//================================GETC==================================================================================
//================================GETC==================================================================================
//================================GETC==================================================================================
//================================GETC==================================================================================
//            char c;
//            uint64 volatile sepc = r_sepc() + 4;
//            uint64 volatile sstatus = r_sstatus();
//            asm volatile ("mv %0, a1": "=r"(c)::);
//            //volatile uint64 *uart =  (volatile uint64*)CONSOLE_STATUS;
//            //volatile uint64 *uart1 =  (volatile uint64*)CONSOLE_TX_DATA;
//            volatile uint64 *uart2 =  (volatile uint64*)CONSOLE_RX_DATA;
//            while((CONSOLE_STATUS & CONSOLE_TX_STATUS_BIT) != 0){}
//            *uart2 = (uint64)c;
//            w_sstatus(sstatus);
//            w_sepc(sepc);
//================================GETC==================================================================================
//================================GETC==================================================================================
//================================GETC==================================================================================
//================================GETC==================================================================================
        }
        else if (x==10){

        }
        else {
            // interrupt: no; cause code: environment call from U-mode(8) or S-mode(9)
            uint64 volatile sepc = r_sepc() + 4;
            uint64 volatile sstatus = r_sstatus();
            TCB::timeSliceCounter = 0;
            TCB::dispatch();
            w_sstatus(sstatus);
            w_sepc(sepc);
        }
    } else if (scause == 0x8000000000000001UL) {
// interrupt: yes; cause code: supervisor software interrupt (CLINT; machine timer interrupt)
        mc_sip(SIP_SSIP);
        TCB::timeSliceCounter++;
        if (TCB::timeSliceCounter >= TCB::running->getTimeSlice()) {
            uint64 volatile sepc = r_sepc();
            uint64 volatile sstatus = r_sstatus();
            TCB::timeSliceCounter = 0;
            TCB::dispatch();
            w_sstatus(sstatus);
            w_sepc(sepc);
        }
    } else if (scause == 0x8000000000000009UL) {
// interrupt: yes; cause code: supervisor external interrupt (PLIC; could be keyboard)
//================================GETC==================================================================================
//================================GETC==================================================================================
//================================GETC==================================================================================
//================================GETC==================================================================================

//        //volatile uint64 *uart =  (volatile uint64*)CONSOLE_STATUS;
//        volatile uint64 *uart1 =  (volatile uint64*)CONSOLE_TX_DATA;
//        //volatile uint64 *uart2 =  (volatile uint64*)CONSOLE_RX_DATA;
//        uint64 a = *uart1;
//        if(a == 10) {
//            //asm volatile ("mv a0, %0":: "r"(a): "a0");
//            asm volatile("sd %0, %c1(sp)"::"r"(a), "i"(30 * 8): "memory");
//        }
//================================GETC==================================================================================
//================================GETC==================================================================================
//================================GETC==================================================================================
//================================GETC==================================================================================

        console_handler();
    } else {
// unexpected trap cause
    }
}