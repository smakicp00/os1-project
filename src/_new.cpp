#include "../lib/mem.h"
#include "../h/print.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../lib/console.h"
using size_t = decltype(sizeof(0));

void *operator new(size_t n) {
    return MemoryAllocator::mem_new(n);
    //return __mem_alloc(n);
}


void *operator new[](size_t n) {
    return MemoryAllocator::mem_new(n);
    //return __mem_alloc(n);
}

void operator delete(void *p)

noexcept
{
MemoryAllocator::mem_free(p);
//__mem_free(p);
}

void operator delete[](void *p)

noexcept
{
MemoryAllocator::mem_free(p);
//__mem_free(p);
}