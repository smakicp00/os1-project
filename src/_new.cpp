#include "../lib/mem.h"
#include "../h/print.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../lib/console.h"
using size_t = decltype(sizeof(0));

void *operator new(size_t n) {
    //void*val= __mem_alloc(n);
    void*val = MemoryAllocator::mem_new(n);
    //printInteger((uint64)val);
    //__putc('\n');
    return val;
}


void *operator new[](size_t n) {
    //void*val= __mem_alloc(n);
    void*val = MemoryAllocator::mem_new(n);
    return val;
}

void operator delete(void *p)

noexcept
{
    MemoryAllocator::mem_free(p);

printString("Obrisano");
//__mem_free(p);
}

void operator delete[](void *p)

noexcept
{
MemoryAllocator::mem_free(p);
//__mem_free(p);
}