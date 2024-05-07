#include "stack.h"

#include <stdio.h>

double stack[STACK_CAPACITY];
int stack_size = 0;

bool stack_push(double item) {
    if (stack_size < STACK_CAPACITY) {
        stack[stack_size++] = item;
        return true;
    }
    return false;
}

bool stack_peek(double *item) {
    if (stack_size > 0) {
        *item = stack[stack_size - 1];
        return true;
    }
    return false;
}

bool stack_pop(double *item) {
    if (stack_size > 0) {
        *item = stack[--stack_size];
        return true;
    }
    return false;
}

void stack_clear(void) {
    stack_size = 0;
}

void stack_print(void) {
    if (stack_size == 0) {
        return;
    }
    printf("%.10f", stack[0]);
    for (int i = 1; i < stack_size; i++) {
        printf(" %.10f", stack[i]);
    }
}
