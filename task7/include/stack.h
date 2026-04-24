#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

#define SIZE 100 

typedef struct {
    int data[SIZE]; 
    size_t t;            
} Stack;

void stack_init(Stack* s);

bool stack_empty(const Stack* s);

bool stack_append(Stack* s, int a);

bool stack_delete(Stack* s, int* out);


#endif
