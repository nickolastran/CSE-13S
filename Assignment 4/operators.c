#include "operators.h"

#include "messages.h"
#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double operator_add(double lhs, double rhs) {
    return lhs + rhs;
}

double operator_sub(double lhs, double rhs) {
    return lhs - rhs;
}

double operator_mul(double lhs, double rhs) {
    return lhs * rhs;
}

double operator_div(double lhs, double rhs) {
    if (rhs == 0.0) {
        return nan("nan");
    }
    return lhs / rhs;
}

bool apply_binary_operator(binary_operator_fn op) {
    double lhs, rhs;
    if (stack_size < 2) {
        fprintf(stderr, "%s", ERROR_BINARY_OPERATOR);
        return false;
    }
    assert(stack_pop(&rhs));
    assert(stack_pop(&lhs));
    return stack_push(op(lhs, rhs));
}

bool apply_unary_operator(unary_operator_fn op) {
    double x;
    if (stack_size < 1) {
        fprintf(stderr, "%s", ERROR_UNARY_OPERATOR);
        return false;
    }
    assert(stack_pop(&x));
    return stack_push(op(x));
}

bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);
    if (endptr != s) {
        *d = result;
        return true;
    } else {
        return false;
    }
}
