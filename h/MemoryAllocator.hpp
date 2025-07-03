#ifndef PROJECT_BASE_V1_1_MEMORYALLOCATOR_HPP
#define PROJECT_BASE_V1_1_MEMORYALLOCATOR_HPP

#include "../h/print.hpp"
#include "../h/list.hpp"


struct Node{
    char* addr;
    Node* next;
    Node* prev;
    bool free;
    size_t size;
};



class MemoryAllocator {

private:

    static Node* head;

public:

    static void init();
    static void *mem_new(size_t n);
    static bool mem_free(void* ptr);
};


#endif //PROJECT_BASE_V1_1_MEMORYALLOCATOR_HPP
