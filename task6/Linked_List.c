#include "Linked_List.h"
#include <stdlib.h>
#include <stdio.h>

void list_init(LinkedList* list) {
    if (list == NULL) return;
    list->head = NULL;
    list->size = 0;
}

void list_free(LinkedList* list) {
    if (list == NULL) return;
    
    Node* current = list->head;
    while (current != NULL) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
    list->head = NULL;
    list->size = 0;
}

static Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

int list_push_front(LinkedList* list, int value) {
    if (list == NULL) return -1;

    Node* new_node = create_node(value);
    if (new_node == NULL) return -1;

    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    
    return 0;
}

int list_push_back(LinkedList* list, int value) {
    if (list == NULL) return -1;

    Node* new_node = create_node(value);
    if (new_node == NULL) return -1;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
    return 0;
}

int list_insert_at(LinkedList* list, size_t index, int value) {
    if (list == NULL) return -1;
    
    if (index > list->size) {
        return -1; 
    }

    if (index == 0) {
        return list_push_front(list, value);
    }

    Node* new_node = create_node(value);
    if (new_node == NULL) return -1;

    Node* current = list->head;
    for (size_t i = 0; i < index - 1; ++i) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
    list->size++;

    return 0;
}

int list_remove_at(LinkedList* list, size_t index) {
    if (list == NULL || list->head == NULL) return -1;
    if (index >= list->size) return -1;

    Node* node_to_delete;

    if (index == 0) {
        node_to_delete = list->head;
        list->head = list->head->next;
    } else {
        Node* current = list->head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        node_to_delete = current->next;
        current->next = node_to_delete->next;
    }

    free(node_to_delete);
    list->size--;
    return 0;
}

int* list_find_by_index(LinkedList* list, size_t index) {
    if (list == NULL || index >= list->size) {
        return NULL;
    }

    Node* current = list->head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }

    return &(current->data);
}

size_t list_size(const LinkedList* list) {
    if (list == NULL) return 0;
    return list->size;
}

void list_print(const LinkedList* list) {
    if (list == NULL) {
        printf("List is NULL\n");
        return;
    }
    
    printf("List [size=%zu]: ", list->size);
    Node* current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
