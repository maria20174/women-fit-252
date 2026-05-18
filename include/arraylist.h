#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stddef.h>
#include "allocator.h"

typedef struct {
    IAllocator* alloc;
    void** data;
    size_t size;
    size_t capacity;
} ArrayList;

int arraylist_init(ArrayList* list, IAllocator* alloc, size_t initial_capacity);
void arraylist_destroy(ArrayList* list);

int arraylist_push(ArrayList* list, void* value);
void* arraylist_get(ArrayList* list, size_t index);
int arraylist_set(ArrayList* list, size_t index, void* value);
int arraylist_remove(ArrayList* list, size_t index);

#endif