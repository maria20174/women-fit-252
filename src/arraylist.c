#include "arraylist.h"

#include <string.h>

#define ARRAYLIST_DEFAULT_CAPACITY 4

static int arraylist_resize(ArrayList* list, size_t new_capacity) {
    if (list == NULL || list->alloc == NULL || list->alloc->alloc == NULL || new_capacity == 0) {
        return -1;
    }

    size_t new_size = sizeof(void*) * new_capacity;
    void** new_data = NULL;

    if (list->alloc->realloc != NULL) {
        new_data = (void**)list->alloc->realloc(list->alloc, list->data, new_size);
    }

    if (new_data == NULL) {
        new_data = (void**)list->alloc->alloc(list->alloc, new_size);

        if (new_data == NULL) {
            return -1;
        }

        memcpy(new_data, list->data, sizeof(void*) * list->size);

        if (list->alloc->free != NULL) {
            list->alloc->free(list->alloc, list->data);
        }
    }

    list->data = new_data;
    list->capacity = new_capacity;

    return 0;
}

int arraylist_init(ArrayList* list, IAllocator* alloc, size_t initial_capacity) {
    if (list == NULL || alloc == NULL || alloc->alloc == NULL) {
        return -1;
    }

    if (initial_capacity == 0) {
        initial_capacity = ARRAYLIST_DEFAULT_CAPACITY;
    }

    list->alloc = alloc;
    list->size = 0;
    list->capacity = initial_capacity;

    list->data = (void**)alloc->alloc(alloc, sizeof(void*) * initial_capacity);

    if (list->data == NULL) {
        list->alloc = NULL;
        list->size = 0;
        list->capacity = 0;
        return -1;
    }

    return 0;
}

void arraylist_destroy(ArrayList* list) {
    if (list == NULL || list->alloc == NULL) {
        return;
    }

    if (list->data != NULL && list->alloc->free != NULL) {
        list->alloc->free(list->alloc, list->data);
    }

    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
    list->alloc = NULL;
}

int arraylist_push(ArrayList* list, void* value) {
    if (list == NULL || list->data == NULL) {
        return -1;
    }

    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity * 2;

        if (arraylist_resize(list, new_capacity) != 0) {
            return -1;
        }
    }

    list->data[list->size] = value;
    list->size++;

    return 0;
}

void* arraylist_get(ArrayList* list, size_t index) {
    if (list == NULL || index >= list->size) {
        return NULL;
    }

    return list->data[index];
}

int arraylist_set(ArrayList* list, size_t index, void* value) {
    if (list == NULL || index >= list->size) {
        return -1;
    }

    list->data[index] = value;

    return 0;
}

int arraylist_remove(ArrayList* list, size_t index) {
    if (list == NULL || index >= list->size) {
        return -1;
    }

    for (size_t i = index; i + 1 < list->size; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->size--;

    return 0;
}