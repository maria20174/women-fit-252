#include "hashtable.h"

#include <string.h>

static unsigned long hash_string(const char* key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++) != '\0') {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

static char* hashtable_copy_key(IAllocator* alloc, const char* key) {
    if (alloc == NULL || alloc->alloc == NULL || key == NULL) {
        return NULL;
    }

    size_t length = strlen(key);
    char* copy = (char*)alloc->alloc(alloc, length + 1);

    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, key, length + 1);

    return copy;
}

int hashtable_init(HashTable* table, IAllocator* alloc, size_t bucket_count) {
    if (table == NULL || alloc == NULL || alloc->alloc == NULL || bucket_count == 0) {
        return -1;
    }

    table->alloc = alloc;
    table->bucket_count = bucket_count;
    table->size = 0;

    table->buckets = (HashNode**)alloc->alloc(alloc, sizeof(HashNode*) * bucket_count);

    if (table->buckets == NULL) {
        table->alloc = NULL;
        table->bucket_count = 0;
        table->size = 0;
        return -1;
    }

    for (size_t i = 0; i < bucket_count; i++) {
        table->buckets[i] = NULL;
    }

    return 0;
}

void hashtable_destroy(HashTable* table) {
    if (table == NULL || table->alloc == NULL || table->buckets == NULL) {
        return;
    }

    for (size_t i = 0; i < table->bucket_count; i++) {
        HashNode* current = table->buckets[i];

        while (current != NULL) {
            HashNode* next = current->next;

            if (current->key != NULL && table->alloc->free != NULL) {
                table->alloc->free(table->alloc, current->key);
            }

            if (table->alloc->free != NULL) {
                table->alloc->free(table->alloc, current);
            }

            current = next;
        }
    }

    if (table->alloc->free != NULL) {
        table->alloc->free(table->alloc, table->buckets);
    }

    table->buckets = NULL;
    table->bucket_count = 0;
    table->size = 0;
    table->alloc = NULL;
}

int hashtable_insert(HashTable* table, const char* key, void* value) {
    if (table == NULL || table->alloc == NULL || table->buckets == NULL || key == NULL) {
        return -1;
    }

    size_t index = hash_string(key) % table->bucket_count;
    HashNode* current = table->buckets[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 0;
        }

        current = current->next;
    }

    if (table->alloc->alloc == NULL) {
        return -1;
    }

    HashNode* node = (HashNode*)table->alloc->alloc(table->alloc, sizeof(HashNode));

    if (node == NULL) {
        return -1;
    }

    node->key = hashtable_copy_key(table->alloc, key);

    if (node->key == NULL) {
        if (table->alloc->free != NULL) {
            table->alloc->free(table->alloc, node);
        }
        return -1;
    }

    node->value = value;
    node->next = table->buckets[index];

    table->buckets[index] = node;
    table->size++;

    return 0;
}

void* hashtable_get(HashTable* table, const char* key) {
    if (table == NULL || table->buckets == NULL || key == NULL || table->bucket_count == 0) {
        return NULL;
    }

    size_t index = hash_string(key) % table->bucket_count;
    HashNode* current = table->buckets[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }

        current = current->next;
    }

    return NULL;
}

int hashtable_remove(HashTable* table, const char* key) {
    if (table == NULL || table->alloc == NULL || table->buckets == NULL || key == NULL) {
        return -1;
    }

    size_t index = hash_string(key) % table->bucket_count;

    HashNode* current = table->buckets[index];
    HashNode* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (previous == NULL) {
                table->buckets[index] = current->next;
            } else {
                previous->next = current->next;
            }

            if (current->key != NULL && table->alloc->free != NULL) {
                table->alloc->free(table->alloc, current->key);
            }

            if (table->alloc->free != NULL) {
                table->alloc->free(table->alloc, current);
            }

            table->size--;

            return 0;
        }

        previous = current;
        current = current->next;
    }

    return -1;
}