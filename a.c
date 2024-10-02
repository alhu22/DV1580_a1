#include "memory_manager.c"
#include "linked_list.h"
#include <stdio.h>  
#include <stdlib.h>


void list_init(Node** head, size_t size){
    *head = (Node*)mem_alloc(size);
    (*head)->next = NULL;
}
void list_insert(Node** head, uint16_t data){
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

void list_insert_after(Node* head, uint16_t data){
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    new_node->data = data;
    new_node->next = head->next;
    head->next = new_node;
}


void list_insert_before(Node** head, Node* next_node, uint16_t data){
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    new_node->data = data;
    new_node->next = next_node;
    Node* current = *head;
    Node* prev = NULL;
    while(current != next_node){
        prev = current;
        current = current->next;
    }
    if(prev == NULL){
        *head = new_node;
    }else{
        prev->next = new_node;
    }
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

void list_display(Node** head){
    Node* current = *head;
    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void list_display_range(Node** head, Node* start_node, Node* end_node){
    Node* current = start_node;
    while(current != end_node){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
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

void list_delete(Node** head, uint16_t data){
    Node* current = *head;
    Node* prev = NULL;
    while(current != NULL){
        if(current->data == data){
            if(prev == NULL){
                *head = current->next;
            }else{
                prev->next = current->next;
            }
            mem_free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
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

