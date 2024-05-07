#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    double angle = 40.0;
    printf("Test Sin(%f) = %f\n", angle, Sin(angle));
    printf("Test sin(%f) = %f\n", angle, sin(angle));

    printf("Test Cos(%f) = %f\n", angle, Cos(angle));
    printf("Test cos(%f) = %f\n", angle, cos(angle));

    printf("Test Tan(%f) = %f\n", angle, Tan(angle));
    printf("Test tan(%f) = %f\n", angle, tan(angle));

    double ite;
    stack_push(2.42);
    stack_push(-52.1);
    stack_print();
    stack_pop(&ite);
    printf("\n");

    stack_peek(&ite);
    if (!stack_peek(&ite)) {
        printf("Incorrect");
    } else {
        printf("%f\n", ite);
    }

    for (int i = 0; i <= 10; i++) {
        printf("%.16f\n", Tan(i) - tan(i));
    }

    stack_print();
    printf("\n");
    stack_clear();
    stack_print();
}
