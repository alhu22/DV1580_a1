#include "linked_list.h"
#include <stdio.h>  
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include "memory_manager.h"
#include <string.h>

// Initialize the linked list  -----------------------------------------------------------------------

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
    // If the list is empty
    if (current == NULL) {
        printf("[]");
        return;
    }
    printf("[");
    printf("%d", current->data);
    current = current->next;
    while (current != NULL) {
        printf(", %d", current->data);
        current = current->next;
    }
    printf("]");
}

void list_display_range(Node** head, Node* start_node, Node* end_node) {
    // If the list is empty
    if (*head == NULL) {
        printf("[]");
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
        printf("[]");
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






