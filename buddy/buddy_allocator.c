#include "buddy_allocator.h"
#include <string.h>

#define LEVELLING_8(x) (((x) + 7) & ~7)

static size_t block_size(BuddyCtx* ctx, int order) 
{
    return ctx->min_block* (1 << order);
}

void init(BuddyCtx* ctx, void* buffer, size_t size, size_t min_block_size) {
    if (!ctx || !buffer || size == 0) 
    {
        return;
    }
    size_t min = LEVELLING_8(min_block_size);
    if (min < sizeof(Block)) {
        min = ALIGN_8(sizeof(Block));
    }

    ctx->buffer = (char*)buffer;
    ctx->min_block = min;
    
    ctx->max_order = 0;
    size_t temp = size / min;
    while (temp > 1) {
        ctx->max_order++;
        temp /= 2;
    }

    for (int i = 0; i <= ctx->max_order; i++) {
        ctx->free_lists[i] = NULL;
    }

    Block* initial = (Block*)ctx->buffer;
    initial->order = ctx->max_order;
    initial->is_free = 1;
    initial->next_free = NULL;
    ctx->free_lists[ctx->max_order] = initial;
}

void* buddy_alloc(BuddyCtx* ctx, size_t bytes) {
    if (!ctx || bytes == 0) return NULL;

    size_t total_needed = ALIGN_8(bytes + sizeof(Block));

    int need_order = 0;
    while (get_block_size(ctx, need_order) < total_needed && need_order < ctx->max_order) {
        need_order++;
    }

    int order = need_order;
    while (order <= ctx->max_order && ctx->free_lists[order] == NULL) {
        order++;
    }

    if (order > ctx->max_order) return NULL;

    Block* block = ctx->free_lists[order];
    ctx->free_lists[order] = block->next_free;

    while (order > need_order) {
        order--;
        size_t half_size = get_block_size(ctx, order);
        
        Block* buddy = (Block*)((char*)block + half_size);
        buddy->order = order;
        buddy->is_free = 1;
        buddy->next_free = ctx->free_lists[order];
        
        ctx->free_lists[order] = buddy;
        block->order = order;
    }

    block->is_free = 0;
    return (void*)((char*)block + sizeof(Block));
}

void buddy_free(BuddyCtx* ctx, void* ptr) {
    if (!ctx || !ptr) return;

    Block* block = (Block*)((char*)ptr - sizeof(Block));
    
    if (block->is_free) return; 

    block->is_free = 1;
    int order = block->order;
    
    block->next_free = ctx->free_lists[order];
    ctx->free_lists[order] = block;
}

void* buddy_realloc(BuddyCtx* ctx, void* ptr, size_t new_size) {
    if (!ptr) return buddy_alloc(ctx, new_size);
    if (new_size == 0) {
        buddy_free(ctx, ptr);
        return NULL;
    }

    void* new_ptr = buddy_alloc(ctx, new_size);
    if (!new_ptr) return NULL;

    memcpy(new_ptr, ptr, new_size); 
    
    buddy_free(ctx, ptr);
    return new_ptr;
}
