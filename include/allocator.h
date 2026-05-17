#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>
#include <stdlib.h>

typedef struct IAllocator {
    void*  (*alloc)(struct IAllocator* self, size_t size);
    void   (*free)(struct IAllocator* self, void* ptr);
    void*  (*realloc)(struct IAllocator* self, void* ptr, size_t new_size);
    void   (*reset)(struct IAllocator* self);
    void*  ctx;  
} IAllocator;

static void stub_free(IAllocator* self, void* ptr) {
    (void)self;
    (void)ptr;
}

static void* stub_realloc(IAllocator* self, void* ptr, size_t new_size) {
    (void)self;
    (void)ptr;
    (void)new_size;
    return NULL;  
}

static void stub_reset(IAllocator* self) {
    (void)self;
}

static void* sys_alloc_impl(IAllocator* self, size_t size) {
    (void)self;
    return malloc(size);
}

static void sys_free_impl(IAllocator* self, void* ptr) {
    (void)self;
    free(ptr);
}

static void* sys_realloc_impl(IAllocator* self, void* ptr, size_t new_size) {
    (void)self;
    return realloc(ptr, new_size);
}

static void sys_reset_impl(IAllocator* self) {
    (void)self;
}

static IAllocator create_sys_alloc(void) {
    IAllocator alloc;
    alloc.alloc    = sys_alloc_impl;
    alloc.free     = sys_free_impl;
    alloc.realloc  = sys_realloc_impl;
    alloc.reset    = sys_reset_impl;
    alloc.ctx      = NULL;
    return alloc;
}

static inline void* i_alloc(IAllocator* a, size_t sz) {
    return a->alloc(a, sz);
}

static inline void i_free(IAllocator* a, void* ptr) {
    a->free(a, ptr);
}

static inline void* i_realloc(IAllocator* a, void* ptr, size_t sz) {
    return a->realloc(a, ptr, sz);
}

static inline void i_reset(IAllocator* a) {
    a->reset(a);
}

#endif
