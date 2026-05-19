#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linear_allocator.h"

void test_linear_1() 
{
    char buffer[1024];
    LinearCtx ctx;
    init(&ctx, buffer, sizeof(buffer));
    void* p1 = alloc(&ctx, 10);
    void* p2 = alloc(&ctx, 20);
    assert(p1 != NULL);
    assert(p2 != NULL);
    assert(p1 != p2);
    assert(((size_t)p1 % 8) == 0);
    assert(((size_t)p2 % 8) == 0);
    memset(p1, 'A', 10);
    memset(p2, 'B', 20);
    assert(((char*)p1)[0] == 'A');
    assert(((char*)p2)[0] == 'B');

    printf("Тест 1 выполнен\n");
}

void test_linear_2() 
{
    char buffer[100];
    LinearCtx ctx;
    init(&ctx, buffer, sizeof(buffer));
    void* p1 = alloc(&ctx, 90);
    assert(p1 != NULL);
    void* p2 = alloc(&ctx, 20);
    assert(p2 == NULL);
    printf("Тест 2 выполнен\n");
}

void test_linear_3() {
    char buffer[1024];
    LinearCtx ctx;
    init(&ctx, buffer, sizeof(buffer));
    void* p1 = alloc(&ctx, 50);
    reset(&ctx);
    void* p2 = alloc(&ctx, 50);
    assert(p1 == p2);
    printf("Тест 3 выполнен\n");
}

int main() {
    test_linear_1();
    test_linear_2();
    test_linear_3();
    return 0;
}
