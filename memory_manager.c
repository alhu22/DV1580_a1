#include <stdio.h>  
#include <stdlib.h>
#include <stdbool.h>
#include "memory_manager.h"
#include <string.h>

void* memory_pool;
Block* head_pool;

void mem_init(int size) {
    memory_pool = malloc(size);
    if (memory_pool == NULL) {
        printf("Failed to allocate memory pool.\n");
        return;
    }

    // Allocate memory for the head block structure
    head_pool = (Block*)malloc(sizeof(Block));
    if (head_pool == NULL) {
        printf("Failed to allocate head block.\n");
        free(memory_pool);
        return;
    }
    // Initialize the head block
    head_pool->address = memory_pool;
    head_pool->size = size;
    head_pool->is_free = true;
    head_pool->next = NULL;
}

// Allocate memory from the memory pool
void* mem_alloc(int size) {
    Block* current = head_pool;

    while (current != NULL) {
        if (current->is_free && current->size >= size) {
            current->is_free = false;
            Block* new_block = (Block*)malloc(sizeof(Block));
            new_block->size = current->size - size;
            new_block->address = current->address + size;
            new_block->is_free = true;
            new_block->next = current->next;

            current->size = size;
            current->next = new_block;
            return current->address;
        }
        current = current->next;
    }
    return NULL;
}

// Resize an allocated memory block
void* mem_resize(void* block, int size) {
    Block* current = head_pool;
    while (current != NULL) {
        if (current->address == block) {
            if (current->size >= size) {
                current->size = size;
                return block;
            } else {
                // Allocate a new block and copy the data
                void* new_block = mem_alloc(size);
                if (new_block == NULL) {
                    return NULL;
                }
                memcpy(new_block, block, current->size);
                mem_free(block);
                return new_block;
            }
        }
        current = current->next;
    }
    return NULL;
}

// Free an allocated memory block
void mem_free(void* block) {
    Block* current = head_pool;
    while (current != NULL) {
        if (current->address == block) {
            current->is_free = true;

            // Try to merge with the next block if it's also free
            if (current->next != NULL && current->next->is_free) {
                current->size += current->next->size + sizeof(Block);
                Block* temp = current->next;
                current->next = current->next->next;
                free(temp);
            }
            return;
        }
        current = current->next;
    }
}

// Deallocate the memory pool
void mem_deinit() {
    Block* current = head_pool;
    while (current != NULL) {
        Block* temp = current;
        current = current->next;
        free(temp);
    }
    free(memory_pool);
}


// Print all blocks in the memory pool
void print_all_blocks() {
    Block* current = head_pool;
    printf("Memory blocks:\n");
    while (current != NULL) {
        printf("Block at %p, size: %d, %s\n",
               current->address, current->size,
               current->is_free ? "free" : "allocated");
        current = current->next;
    }
}

