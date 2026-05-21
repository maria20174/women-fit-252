#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <stddef.h>

typedef struct {
    void* buffer;
    size_t size;
    size_t offset;
} LinearCtx;

void l_init(LinearCtx* ctx, void* buffer, size_t size);
void* l_alloc(LinearCtx* ctx, size_t bytes);
void l_reset(LinearCtx* ctx);
void l_free(LinearCtx* ctx, void* address);

#endif
