#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "buddy_allocator.h"

void test_buddy_basic() {
    printf("[TEST] Buddy: Basic Allocation\n");
    char buffer[4096];
    BuddyCtx ctx;
    buddy_init(&ctx, buffer, sizeof(buffer), 32);

    void* p1 = buddy_alloc(&ctx, 10);
    assert(p1 != NULL);
    
    assert(((size_t)p1 % 8) == 0);

    printf("  -> PASS\n");
}

void test_buddy_multiple_sizes() {
    printf("[TEST] Buddy: Different Sizes\n");
    char buffer[4096];
    BuddyCtx ctx;
    buddy_init(&ctx, buffer, sizeof(buffer), 32);

    void* small = buddy_alloc(&ctx, 10);
    void* large = buddy_alloc(&ctx, 200);

    assert(small != NULL);
    assert(large != NULL);
    assert(small != large);

    printf("  -> PASS\n");
}

void test_buddy_realloc() {
    printf("[TEST] Buddy: Realloc & Data Integrity\n");
    char buffer[4096];
    BuddyCtx ctx;
    buddy_init(&ctx, buffer, sizeof(buffer), 32);

    void* p1 = buddy_alloc(&ctx, 20);
    strcpy((char*)p1, "Hello World");

    void* p2 = buddy_realloc(&ctx, p1, 100);
    assert(p2 != NULL);
    
    assert(strcmp((char*)p2, "Hello World") == 0);

    buddy_free(&ctx, p2);
    printf("  -> PASS\n");
}

void test_buddy_overflow() {
    printf("[TEST] Buddy: Overflow\n");
    char buffer[128];
    BuddyCtx ctx;
    buddy_init(&ctx, buffer, sizeof(buffer), 32);

    void* p = buddy_alloc(&ctx, 1000);
    assert(p == NULL);

    printf("  -> PASS\n");
}

int main() {
    test_buddy_basic();
    test_buddy_multiple_sizes();
    test_buddy_realloc();
    test_buddy_overflow();
    printf("============================\n");
    printf("BUDDY TESTS PASSED\n");
    printf("============================\n");
    return 0;
}