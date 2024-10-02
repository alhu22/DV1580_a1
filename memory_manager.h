#ifndef MYFUNCTIONS_H  // Include guard to prevent multiple inclusions
#define MYFUNCTIONS_H

#include <stdbool.h>

typedef struct Block {
    int size;
    bool is_free;
    void* address;
    struct Block* next;
} Block;

void* memory_pool;
Block* head_pool;

void mem_init(int size);
void* mem_alloc(int size);
void mem_free(void* block);
void* mem_resize(void* block, int size);
void mem_deinit();

#endif
