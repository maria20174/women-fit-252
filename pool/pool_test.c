#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pool_allocator.h"

void test_pool_1() 
{
    char buffer[4 * 64];
    PoolCtx ctx;
    init(&ctx, buffer, sizeof(buffer), 64);
    void* b1 = alloc(&ctx);
    void* b2 = alloc(&ctx);
    assert(b1 != NULL);
    assert(b2 != NULL);
    assert(b1 != b2);
    printf("Тест 1 выполнен\n");
}

void test_pool_2() 
{
    char buffer[2 * 64];
    PoolCtx ctx;
    init(&ctx, buffer, sizeof(buffer), 64);
    alloc(&ctx);
    alloc(&ctx);
    void* b3 = alloc(&ctx);
    assert(b3 == NULL);
    printf("Тест 2 выполнен\n");
}

void test_pool_recycling() 
{
    char buffer[2 * 64];
    PoolCtx ctx;
    init(&ctx, buffer, sizeof(buffer), 64);
    void* b1 = alloc(&ctx);
    free(&ctx, b1);
    void* b2 = alloc(&ctx);
    assert(b1 == b2);
    printf("Тест 3 выполнен\n");
}

int main() {
    test_pool_1();
    test_pool_2();
    test_pool_3();
    return 0;
}