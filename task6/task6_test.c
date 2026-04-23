#include <stdio.h>
#include <assert.h>
#include "Linked_List.h"

#define TEST_START(name) printf("\n--- Test: %s ---\n", name)
#define TEST_PASS() printf("PASSED\n")

void test_init_and_size() {
    TEST_START("Initialization and Size");
    LinkedList list;
    list_init(&list);
    
    assert(list_size(&list) == 0);
    assert(list.head == NULL);
    
    TEST_PASS();
    list_free(&list);
}

void test_push_front() {
    TEST_START("Push Front");
    LinkedList list;
    list_init(&list);

    list_push_front(&list, 10);
    assert(list_size(&list) == 1);
    assert(*list_find_by_index(&list, 0) == 10);

    list_push_front(&list, 20);
    assert(list_size(&list) == 2);
    assert(*list_find_by_index(&list, 0) == 20);
    assert(*list_find_by_index(&list, 1) == 10);

    list_print(&list);
    TEST_PASS();
    list_free(&list);
}

void test_push_back() {
    TEST_START("Push Back");
    LinkedList list;
    list_init(&list);

    list_push_back(&list, 10);
    list_push_back(&list, 20);
    list_push_back(&list, 30);

    assert(list_size(&list) == 3);
    assert(*list_find_by_index(&list, 0) == 10);
    assert(*list_find_by_index(&list, 1) == 20);
    assert(*list_find_by_index(&list, 2) == 30);

    list_print(&list);
    TEST_PASS();
    list_free(&list);
}

void test_insert_at() {
    TEST_START("Insert At (Middle/Start/End)");
    LinkedList list;
    list_init(&list);

    list_push_back(&list, 10);
    list_push_back(&list, 30);

    int res = list_insert_at(&list, 1, 20);
    assert(res == 0);
    assert(list_size(&list) == 3);
    assert(*list_find_by_index(&list, 0) == 10);
    assert(*list_find_by_index(&list, 1) == 20);
    assert(*list_find_by_index(&list, 2) == 30);

    list_insert_at(&list, 0, 5);
    assert(*list_find_by_index(&list, 0) == 5);

    list_insert_at(&list, list_size(&list), 50);
    assert(*list_find_by_index(&list, list_size(&list) - 1) == 50);

    res = list_insert_at(&list, 100, 999);
    assert(res == -1);

    list_print(&list);
    TEST_PASS();
    list_free(&list);
}

void test_remove_at() {
    TEST_START("Remove At");
    LinkedList list;
    list_init(&list);

    list_push_back(&list, 10);
    list_push_back(&list, 20);
    list_push_back(&list, 30);
    list_push_back(&list, 40);

    int res = list_remove_at(&list, 1);
    assert(res == 0);
    assert(list_size(&list) == 3);
    assert(*list_find_by_index(&list, 1) == 30);

    list_remove_at(&list, 0);
    assert(*list_find_by_index(&list, 0) == 30);

    list_remove_at(&list, 1);
    assert(list_size(&list) == 1);
    assert(*list_find_by_index(&list, 0) == 30);

    res = list_remove_at(&list, 5);
    assert(res == -1);
    
    list_remove_at(&list, 0);
    assert(list_size(&list) == 0);
    assert(list.head == NULL);

    list_print(&list);
    TEST_PASS();
    list_free(&list);
}

void test_find_by_index() {
    TEST_START("Find By Index");
    LinkedList list;
    list_init(&list);
    
    list_push_back(&list, 100);
    
    int* val = list_find_by_index(&list, 0);
    assert(val != NULL);
    assert(*val == 100);

    val = list_find_by_index(&list, 1);
    assert(val == NULL);

    list_remove_at(&list, 0);
    val = list_find_by_index(&list, 0);
    assert(val == NULL);

    TEST_PASS();
    list_free(&list);
}

int main() {
    printf("Starting Linked List Tests...\n");

    test_init_and_size();
    test_push_front();
    test_push_back();
    test_insert_at();
    test_remove_at();
    test_find_by_index();

    printf("\nAll tests completed successfully!\n");
    return 0;
}