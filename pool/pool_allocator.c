#include "pool_allocator.h"

#define LEVELLING_8(x) (((x) + 7) & ~7)

void init(PoolCtx* ctx, void* buffer, size_t buffer_size, size_t block_size) {
    if (!ctx || !buffer || block_size == 0)
    {
    return;
    }
    size_t real_size = LEVELLING_8(block_size);
    if (real_size < sizeof(Node)) 
    {
        real_size = LEVELLING_8(sizeof(Node));
    }
    ctx->buffer = (char*)buffer;
    ctx->block_size = real_size;
    ctx->blocks = buffer_size / real_size;
    ctx->free_block = NULL;

    if (ctx->blocks == 0)
    {
        return;
    }
    for (size_t i = 0; i < ctx->blocks; i++) {
        Node* node = (Node*)(ctx->buffer + i * real_size);
        node->next = ctx->free_block;
        ctx->free_block = node;
    }
}
void* alloc(PoolCtx* ctx) {
    if (!ctx || !ctx->free_block)
    {
        return NULL;
    }
    Node* node = ctx->free_block;
    ctx->free_block = node->next;
    return (void*)node;
}
void free(PoolCtx* ctx, void* address) {
    if (!ctx || !address)
    {
        return;
    }
    Node* node = (Node*)address;
    node->next = ctx->free_block;
    ctx->free_block = node;
}
