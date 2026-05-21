#include "linear_allocator.h"
#define LEVELLING_8(x) (((x) + 7) & ~7)

void l_init(LinearCtx* ctx, void* buffer, size_t size) 
{
    if (!ctx || !buffer || size == 0) 
    {
        return;
    }
    ctx->buffer = (char*)buffer;
    ctx->size = size;
    ctx->offset = 0;
}
void* l_alloc(LinearCtx* ctx, size_t bytes) 
{
    if (!ctx || bytes == 0)
    {
        return NULL;
    }
    size_t levelling_bytes = LEVELLING_8(bytes);

    if (ctx->offset + levelling_bytes > ctx->size) 
    {
        return NULL;
    }
    void* address = ctx->buffer + ctx->offset;
    ctx->offset += levelling_bytes;  
    return address;
}
void l_reset(LinearCtx* ctx) 
{
    if (ctx)
    {
        ctx->offset = 0;
    } 
}
void l_free(LinearCtx* ctx, void* address) 
{
    (void)ctx; 
    (void)address;
}
