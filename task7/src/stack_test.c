#include <stdio.h>
#include <assert.h>
#include "stack.h"

int main(void) {
    Stack s;
    int a;
    
    stack_init(&s);
    assert(stack_empty(&s) == true);
    printf("[");
    for (size_t i = 0; i < s.t; i++) {
        printf("%d", s.data[i]);
        if (i < s.t - 1) printf(", ");
    }
    printf("]\n");

    assert(stack_append(&s, 10) == true);
    assert(stack_append(&s, 20) == true);
    assert(stack_empty(&s) == false);
    printf("[");
    for (size_t i = 0; i < s.t; i++) {
        printf("%d", s.data[i]);
        if (i < s.t - 1) printf(", ");
    }
    printf("]\n");

    assert(stack_delete(&s, &a) == true);
    assert(a == 20); 
    assert(stack_delete(&s, &a) == true);
    assert(a == 10);
    assert(stack_empty(&s) == true);
    printf("[");
    for (size_t i = 0; i < s.t; i++) {
        printf("%d", s.data[i]);
        if (i < s.t - 1) printf(", ");
    }
    printf("]\n");
 
    assert(stack_delete(&s, &a) == false);
    printf("[");
    for (size_t i = 0; i < s.t; i++) {
        printf("%d", s.data[i]);
        if (i < s.t - 1) printf(", ");
    }
    printf("]\n");

    stack_init(&s);
}
