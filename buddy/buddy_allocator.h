#ifndef BUDDY_ALLOCATOR_H
#define BUDDY_ALLOCATOR_H
#include <stddef.h>
#define MAX_ORDER 8

typedef struct Block {
    int order;
    int is_free;
    struct Block* next_free;
} Block;
typedef struct {
    void* buffer;
    size_t min_block;
    int max_order;
    Block* free_block[MAX_ORDER + 1];
} BuddyCtx;
void b_init(BuddyCtx* ctx, void* buffer, size_t size, size_t min_block);
void* b_alloc(BuddyCtx* ctx, size_t bytes);
void b_free(BuddyCtx* ctx, void* ptr);
void* b_realloc(BuddyCtx* ctx, void* ptr, size_t new_size);
#endif
