#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include <stddef.h>

typedef struct {
    void* buffer;
    size_t size;
    size_t offset;
} LinearCtx;

void init(LinearCtx* ctx, void* buffer, size_t size);
void* alloc(LinearCtx* ctx, size_t bytes);
void eset(LinearCtx* ctx);
void free(LinearCtx* ctx, void* address);

#endif
