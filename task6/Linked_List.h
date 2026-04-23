#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    size_t size;
} LinkedList;

void list_init(LinkedList* list);
void list_free(LinkedList* list);
int list_push_front(LinkedList* list, int value);
int list_push_back(LinkedList* list, int value);
int list_insert_at(LinkedList* list, size_t index, int value);
int list_remove_at(LinkedList* list, size_t index);
int* list_find_by_index(LinkedList* list, size_t index);
size_t list_size(const LinkedList* list);
void list_print(const LinkedList* list);

#endif