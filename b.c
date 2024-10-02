// #include "memory_manager.h"
#include "common_defs.h"
#include "linked_list.h"
#include <stdio.h>  
#include <stdlib.h>

#include <stdbool.h>
#include "memory_manager.h"
#include <string.h>

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


























void list_init(Node** head, size_t size){
    mem_init(size);
}

void list_insert(Node** head, uint16_t data){
    Node* new_node = mem_alloc(sizeof(Node));
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


};

void list_insert_after(Node* prev_node, uint16_t data){
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    new_node->data = data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;

};

void list_insert_before(Node** head, Node* next_node, uint16_t data){
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    new_node->data = data;
    new_node->next = next_node;
    Node* current = *head;
    if(next_node == *head){
        new_node->next = *head;
        *head = new_node;
        return;
    }
    while(current->next != next_node){
        current = current->next;
    }
    current->next = new_node;

}

void list_delete(Node** head, uint16_t data){
    Node* current = *head;
    Node* prev = NULL;
    while(current->data != data){
        prev = current;
        current = current->next;
    }
    if(prev == NULL){
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    mem_free(current);
}

Node* list_search(Node** head, uint16_t data){
    Node* current = *head;
    while(current != NULL){
        if(current->data == data){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void list_display(Node** head) {
    Node* current = *head;

    // Handle the case when the list is empty
    if (current == NULL) {
        printf("[]\n");
        return;
    }

    printf("[");  // Start the list format

    // Print the first node's data
    printf("%d", current->data);
    current = current->next;

    // Loop through and print the remaining nodes with commas separating them
    while (current != NULL) {
        printf(", %d", current->data);
        current = current->next;
    }

    printf("]\n");  // End the list format
}

void list_display_range(Node** head, Node* start_node, Node* end_node) {
    if (head == NULL || *head == NULL) {
        printf("[]\n");
        return;
    }

    Node* current = *head;

    // Traverse to start_node if specified
    if (start_node) {
        while (current != NULL && current != start_node) {
            current = current->next;
        }
    }

    if (current == NULL) {
        // If start_node is not found or the list is empty
        printf("[]\n");
        return;
    }

    // Start printing the list range
    printf("[");
    bool first = true;  // For proper comma placement
    while (current != NULL && (end_node == NULL || current != end_node->next)) {
        if (!first) {
            printf(", ");
        }
        printf("%d", current->data);
        first = false;
        current = current->next;
    }
    printf("]");
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
    Node* temp;
    while(current != NULL){
        temp = current;
        current = current->next;
        mem_free(temp);
    }
    *head = NULL;
}






