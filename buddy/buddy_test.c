#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "buddy_allocator.h"
void test_buddy_1() 
{
    char buffer[4096];
    BuddyCtx ctx;
    init(&ctx, buffer, sizeof(buffer), 32);
    void* p1 = alloc(&ctx, 10);
    assert(p1 != NULL);
    assert(((size_t)p1 % 8) == 0);
    printf("Тест 1 выполнен\n");
}
void test_buddy_2() 
{
    char buffer[4096];
    BuddyCtx ctx;
    init(&ctx, buffer, sizeof(buffer), 32);
    void* small = alloc(&ctx, 10);
    void* large = alloc(&ctx, 200);
    assert(small != NULL);
    assert(large != NULL);
    assert(small != large);
    printf("Тест 2 выполнен\n");
}
void test_buddy_3() 
{
    char buffer[4096];
    BuddyCtx ctx;
    buddy_init(&ctx, buffer, sizeof(buffer), 32);
    void* p1 = alloc(&ctx, 20);
    strcpy((char*)p1, "Hello World");
    void* p2 = realloc(&ctx, p1, 100);
    assert(p2 != NULL);
    assert(strcmp((char*)p2, "Hello World") == 0);
    free(&ctx, p2);
    printf("Тест 3 выполнен\n");
}
void test_buddy_4() 
{
    char buffer[128];
    BuddyCtx ctx;
    init(&ctx, buffer, sizeof(buffer), 32);
    void* p = alloc(&ctx, 1000);
    assert(p == NULL);
    printf("Тест 4 выполнен\n");
}

int main() 
{
    test_buddy_1();
    test_buddy_2();
    test_buddy_3();
    test_buddy_4();
    return 0;
}
