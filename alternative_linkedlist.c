#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "linked_list.h"

#include <stdlib.h>
#include <stdbool.h>
#include "memory_manager.h"

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

    Block* prev = current;
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
        prev = current;
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

typedef struct Node {
uint16_t data; 
struct Node* next;
} Node;

void list_init(Node** head, int size) {
    *head = NULL;
}

void list_insert(Node** head, int data) {
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void list_insert_after(Node* prev_node, int data){
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    new_node->data = data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

void list_insert_before(Node** head, Node* next_node, int data){
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    new_node->data = data;
    new_node->next = next_node;
    Node* current = *head;
    while(current->next != next_node){
        current = current->next;
    }
    current->next = new_node;

}

void list_delete(Node** head, int data){
    Node* current = *head;
    Node* prev = NULL;
    while(current->data != data){
        prev = current;
        current = current->next;
    }
    if(current->next != NULL){
        prev->next = current->next;
    }else{
        prev->next = NULL;
    }
    mem_free(current);
}
Node* list_search(Node** head, int data){
    Node* current = *head;
    while(current->data != data){
        current = current->next;
    }
    return current;
}

void list_display(Node** head, Node* start_node, Node* end_node){
    Node* current = start_node;
    while(current != end_node){
        printf("%d\n", current->data);
        current = current->next;
    }
}

int list_count_nodes(Node** head){
    Node* current = *head;
    int count = 0;
    while(current != NULL){
        count++;
        current = current->next;
    }
    return count;
}

void list_cleanup(Node** head){
    Node* current = *head;
    Node* next;
    while(current != NULL){
        next = current->next;
        mem_free(current);
        current = next;
    }
    *head = NULL;
}


void print_all_Nodes(Node** head){
    Node* current = *head;
    while(current != NULL){
        printf("Node at %p, Data: %d\n", (void*)current, current->data);
        current = current->next;
    }
}
