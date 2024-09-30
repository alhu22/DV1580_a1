#ifndef MEM_LIST_H
#define MEM_LIST_H

#include <stdint.h>
#include <stddef.h>


typedef struct Block {
    int size;
    int is_free;
    struct Block *next;
} Block;

extern int* memory_pool;
extern Block* head_pool;

void mem_init(int size);
void* mem_alloc(int size);
void mem_free(void* block);
void* mem_resize(void* block, size_t size);
void mem_deinit();

typedef struct Node {
    uint16_t data;
    struct Node* next;
} Node;

void list_init(Node** head);
void list_insert(Node** head, int data);
void list_insert_after(Node* prev_node, int data);
void list_insert_before(Node** head, Node* next_node, int data);
void list_delete(Node** head, int data);
Node* list_search(Node** head, int data);
void list_display(Node** head, Node* start_node, Node* end_node);
int list_count_nodes(Node** head);
void list_cleanup(Node** head);

void print_all_blocks();
void print_all_Nodes(Node** head);

#endif
