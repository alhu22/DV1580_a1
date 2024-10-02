#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
// #include "memory_manager.h"
#include "linked_list.h"


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
