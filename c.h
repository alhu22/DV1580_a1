#ifndef MEM_LIST_H   
#define MEM_LIST_H

#include <stdint.h>
#include <stddef.h>   

void mem_init(int size);
void* mem_alloc(int size);
void mem_free(void* block);
void* mem_resize(void* block, size_t size);
void mem_deinit();

#endif
