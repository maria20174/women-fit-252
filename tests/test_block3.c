#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "arraylist.h"
#include "queue.h"
#include "hashtable.h"
#include "allocator.h"

static void* test_alloc(IAllocator* self, size_t size) {
    (void)self;
    return malloc(size);
}

static void test_free(IAllocator* self, void* ptr) {
    (void)self;
    free(ptr);
}

static void* test_realloc(IAllocator* self, void* ptr, size_t new_size) {
    (void)self;
    return realloc(ptr, new_size);
}

static void test_reset(IAllocator* self) {
    (void)self;
}

static IAllocator create_test_allocator(void) {
    IAllocator allocator;

    allocator.alloc = test_alloc;
    allocator.free = test_free;
    allocator.realloc = test_realloc;
    allocator.reset = test_reset;
    allocator.ctx = NULL;

    return allocator;
}

static void test_arraylist(void) {
    IAllocator allocator = create_test_allocator();

    ArrayList list;
    int values[10];

    assert(arraylist_init(&list, &allocator, 2) == 0);
    assert(list.size == 0);
    assert(list.capacity == 2);

    for (int i = 0; i < 10; i++) {
        values[i] = i + 1;
        assert(arraylist_push(&list, &values[i]) == 0);
    }

    assert(list.size == 10);
    assert(list.capacity >= 10);

    for (int i = 0; i < 10; i++) {
        int* value = (int*)arraylist_get(&list, i);
        assert(value != NULL);
        assert(*value == i + 1);
    }

    int new_value = 100;
    assert(arraylist_set(&list, 3, &new_value) == 0);

    int* checked_value = (int*)arraylist_get(&list, 3);
    assert(checked_value != NULL);
    assert(*checked_value == 100);

    assert(arraylist_remove(&list, 3) == 0);
    assert(list.size == 9);

    checked_value = (int*)arraylist_get(&list, 3);
    assert(checked_value != NULL);
    assert(*checked_value == 5);

    assert(arraylist_get(&list, 100) == NULL);
    assert(arraylist_remove(&list, 100) == -1);

    arraylist_destroy(&list);

    printf("ArrayList test passed\n");
}

static void test_queue(void) {
    IAllocator allocator = create_test_allocator();

    Queue queue;
    int a = 1;
    int b = 2;
    int c = 3;

    queue_init(&queue, &allocator);

    assert(queue_is_empty(&queue) == 1);
    assert(queue_pop(&queue) == NULL);

    assert(queue_push(&queue, &a) == 0);
    assert(queue_push(&queue, &b) == 0);
    assert(queue_push(&queue, &c) == 0);

    assert(queue.size == 3);
    assert(queue_is_empty(&queue) == 0);

    int* value = (int*)queue_peek(&queue);
    assert(value != NULL);
    assert(*value == 1);

    value = (int*)queue_pop(&queue);
    assert(value != NULL);
    assert(*value == 1);

    value = (int*)queue_pop(&queue);
    assert(value != NULL);
    assert(*value == 2);

    value = (int*)queue_pop(&queue);
    assert(value != NULL);
    assert(*value == 3);

    assert(queue_is_empty(&queue) == 1);
    assert(queue_pop(&queue) == NULL);

    queue_destroy(&queue);

    printf("Queue test passed\n");
}

static void test_hashtable(void) {
    IAllocator allocator = create_test_allocator();

    HashTable table;

    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    int updated_value = 100;

    assert(hashtable_init(&table, &allocator, 4) == 0);

    assert(hashtable_insert(&table, "one", &value1) == 0);
    assert(hashtable_insert(&table, "two", &value2) == 0);
    assert(hashtable_insert(&table, "three", &value3) == 0);

    assert(table.size == 3);

    int* result = (int*)hashtable_get(&table, "one");
    assert(result != NULL);
    assert(*result == 10);

    result = (int*)hashtable_get(&table, "two");
    assert(result != NULL);
    assert(*result == 20);

    result = (int*)hashtable_get(&table, "three");
    assert(result != NULL);
    assert(*result == 30);

    assert(hashtable_get(&table, "unknown") == NULL);

    assert(hashtable_insert(&table, "one", &updated_value) == 0);

    result = (int*)hashtable_get(&table, "one");
    assert(result != NULL);
    assert(*result == 100);

    assert(table.size == 3);

    assert(hashtable_remove(&table, "two") == 0);
    assert(hashtable_get(&table, "two") == NULL);
    assert(table.size == 2);

    assert(hashtable_remove(&table, "unknown") == -1);

    hashtable_destroy(&table);

    printf("HashTable test passed\n");
}

int main(void) {
    test_arraylist();
    test_queue();
    test_hashtable();

    printf("All block 3 tests passed\n");

    return 0;
}