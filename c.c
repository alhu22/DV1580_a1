#include <stdio.h>      // printf
#include <stdlib.h>       // malloc
#include <stdint.h>      // uint16_t
#include <stdbool.h>     // bool
#include "common_defs.h"
// #include "test_memory_manager.c"

void *head_pool;
void *tail_pool;
int block_sizes[1024];
bool status[1024] = {true};
int count_block = 0;

void mem_init(int size){
    head_pool = malloc(size);
    block_sizes[count_block] = size;
    tail_pool = head_pool;
}

void* mem_alloc(int size){

    int countsize = 0;
    for (int i=0; i<count_block; i++){        // check previous block
        if (status[i]){
            if (block_sizes[i]>= size){
                // printf("%d\n", countsize);
                status[i] = false;
                block_sizes[i] = size;
                return head_pool + countsize;
            }}
        countsize += block_sizes[i];
            }
    if (block_sizes[count_block] >= size){               // new block
        tail_pool += size;
        block_sizes[count_block+1] = block_sizes[count_block] - size;
        block_sizes[count_block] = size;
        status[count_block] = false;
        count_block++;
        return tail_pool - size;
        }
    return NULL;
}
void *mem_resize(void* block, size_t size){
    int* target = head_pool;
    for (int i=0; i<count_block; i++){
        if (target==block){
            block_sizes[i] = size;
        }
        target += block_sizes[i];
    }
    return block;
}


void mem_deinit(){
    free(head_pool);
}

void mem_free(void*block){
    int* target = head_pool;
    for (int i=0; i<count_block; i++){
        if (target==block){
            status[i] = true;
        }
        target += block_sizes[i];
    }
}

// void test_exceed_cumulative_allocation()
// {
//     printf_yellow("  Testing cumulative allocations exceeding pool size ---> ");
//     mem_init(1024); // Initialize with 1KB of memory
//     void *block1 = mem_alloc(512);
//     my_assert(block1 != NULL);
//     void *block2 = mem_alloc(512);
//     my_assert(block2 != NULL);
//     void *block3 = mem_alloc(100); // This should fail, no space left
//     my_assert(block3 == NULL);
//     mem_free(block1);
//     mem_free(block2);
//     mem_deinit();
//     printf_green("[PASS].\n");
// }

// void test_memory_overcommit()
// {
//     printf_yellow("  Testing memory over-commitment ---> ");
//     mem_init(1024); // Initialize with 1KB of memory

//     void *block1 = mem_alloc(1020); // Allocate almost all memory
//     my_assert(block1 != NULL);
//     void *block2 = mem_alloc(10); // Try allocating beyond the limit
//     my_assert(block2 == NULL);    // Expect NULL because it exceeds available memory

//     mem_free(block1);
//     mem_deinit();
//     printf_green("[PASS].\n");
// }



// int main(){
    // mem_init(1024); 

    // void *block1 = mem_alloc(512);
    // void *block2 = mem_alloc(512);
    // void *block3 = mem_alloc(100); // This should fail, no space left
    // my_assert(block3 == NULL);

    // printf_yellow("  Testing exact fit reuse ---> ");
    // mem_init(1024); // Initialize with 1KB of memory
    // void *block1 = mem_alloc(500);
    // mem_free(block1);
    // void *block2 = mem_alloc(500); // Reuse the exact space freed
    // my_assert(block1 == block2);   // Should be the same address if reused properly
    // mem_free(block2);
    // mem_deinit();
    // printf_green("[PASS].\n");

    // printf_yellow("  Testing exact fit reuse ---> ");
    // mem_init(1024); // Initialize with 1KB of memory
    // void *block1 = mem_alloc(500);
    // mem_free(block1);
    // void *block2 = mem_alloc(500); // Reuse the exact space freed
    // my_assert(block1 == block2);   // Should be the same address if reused properly
    // mem_free(block2);
    // mem_deinit();
    // printf_green("[PASS].\n");

    // test_exceed_cumulative_allocation();
    // test_memory_overcommit();

    // printf("%p\n", tail_pool);

    // for (int i=0; i<=count_block; i++){
    //     printf("%d\n", block_sizes[i]);
    // }

    // mem_deinit();
    // return 0;}



void list_display_range(Node** head, Node* start_node, Node* end_node) {
    // Prints all elements of the list between two nodes (start_node and end_node).
    // If start_node is NULL, it should start from the beginning.
    // If end_node is NULL, it should print until the end.
    // I.e., list_display_range(&head, NULL, NULL) should print all elements of the list.
    // Ranges are inclusive, i.e. list_display_range(&head, 5, 7) in a linked list [1, 2, 3, 4, 5, 6, 7, 8, 9] should print [5, 6, 7].

    if (head != NULL && *head != NULL) { // Check if head is valid and the list is not empty
        Node *current_list_node = *head;
        bool started_printing = false;   // Toggle for when we have started printing
        bool start_from_start = false;   // Toggle for printing everything from the start
        bool print_to_end = false;       // Toggle for printing everything to the end

        if (start_node == NULL) { // If we don't have a start node we should start from the beginning
            start_from_start = true;
        }

        if (end_node == NULL) { // If we don't have an end node we should print to the end
            print_to_end = true;
        }

        printf("[");

        while (current_list_node != NULL) {
            if (start_from_start) { // Toggle for printing everything from the start
                started_printing = true;
            }

            if (current_list_node == start_node && !start_from_start) { // If we reach the start node
                started_printing = true;
            }

            if (started_printing) { // If we have started printing
                printf("%d", current_list_node->data); // Print the data of the current node
                if (current_list_node->next != NULL && current_list_node != end_node) { // If there is a next node and the current is not the end node
                    printf(", ");
                }
            }

            if (current_list_node == end_node && !print_to_end) { // If we reach the end node
                printf("]");
                return;
            }

            current_list_node = current_list_node->next; // Move to the next node
        }
        
        printf("]"); // This is the case where we had an end_node = NULL so we had to print to the end no matter what
    } else {
        printf("[]"); // If the list is empty
    }
}
