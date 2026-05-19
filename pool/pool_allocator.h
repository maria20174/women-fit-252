#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <stddef.h>

typedef struct Node {
    struct Node* next;
} Node;

typedef struct {
    void* buffer;
    size_t block_size;
    size_t blocks;
    Node* free_block;
} PoolCtx;

void init(PoolCtx* ctx, void* buffer, size_t buffer_size, size_t block_size);
void* alloc(PoolCtx* ctx);
void free(PoolCtx* ctx, void* ptr);

#endif
