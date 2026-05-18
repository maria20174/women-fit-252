
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>
#include "allocator.h"

typedef struct HashNode {
    char* key;
    void* value;
    struct HashNode* next;
} HashNode;

typedef struct {
    IAllocator* alloc;
    HashNode** buckets;
    size_t bucket_count;
    size_t size;
} HashTable;

int hashtable_init(HashTable* table, IAllocator* alloc, size_t bucket_count);
void hashtable_destroy(HashTable* table);

int hashtable_insert(HashTable* table, const char* key, void* value);
void* hashtable_get(HashTable* table, const char* key);
int hashtable_remove(HashTable* table, const char* key);

#endif