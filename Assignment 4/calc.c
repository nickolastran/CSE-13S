#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "mh"

int main(int argc, char **argv) {
    int opt;
    bool useLib = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            fprintf(stdout, "%s", USAGE);
            return 0;
            break;
        case 'm': useLib = true;
        default: break;
        }
    }

    char *saveptr;
    char buffer[1024];

    while (fprintf(stderr, "> ") && fgets(buffer, 1024, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0';
        }

        int number_of_tokens = 0;
        char *tokens[100];
        char *token = strtok_r(buffer, " ", &saveptr);

        while (token != NULL) {
            tokens[number_of_tokens] = token;
            number_of_tokens++;
            token = strtok_r(NULL, " ", &saveptr);
        }

        bool error;

        for (int i = 0; i < number_of_tokens; i++) {
            double value;

            if (stack_size >= STACK_CAPACITY) {
                double temp = strtod(tokens[i], NULL);
                fprintf(stderr, ERROR_NO_SPACE, temp);
                break;
            } else if (parse_double(tokens[i], &value) == true) {
                stack_push(value);
            } else if (strcmp(tokens[i], "+") == 0) {
                error = apply_binary_operator(operator_add);
            } else if (strcmp(tokens[i], "-") == 0) {
                error = apply_binary_operator(operator_sub);
            } else if (strcmp(tokens[i], "/") == 0) {
                error = apply_binary_operator(operator_div);
            } else if (strcmp(tokens[i], "*") == 0) {
                error = apply_binary_operator(operator_mul);
            } else if (strcmp(tokens[i], "%") == 0) {
                error = apply_binary_operator(fmod);
            } else if (strcmp(tokens[i], "s") == 0) {
                if (useLib == true) {
                    error = apply_unary_operator(sin);
                } else {
                    error = apply_unary_operator(Sin);
                }
            } else if (strcmp(tokens[i], "c") == 0) {
                if (useLib == true) {
                    error = apply_unary_operator(cos);
                } else {
                    error = apply_unary_operator(Cos);
                }
            } else if (strcmp(tokens[i], "t") == 0) {
                if (useLib == true) {
                    error = apply_unary_operator(tan);
                } else {
                    error = apply_unary_operator(Tan);
                }
            } else if (strcmp(tokens[i], "a") == 0) {
                if (useLib == true) {
                    error = apply_unary_operator(fabs);
                } else {
                    error = apply_unary_operator(Abs);
                }
            } else if (strcmp(tokens[i], "r") == 0) {
                if (useLib == true) {
                    error = apply_unary_operator(sqrt);
                } else {
                    error = apply_unary_operator(Sqrt);
                }
            } else if ((int) strlen(tokens[i]) == 1) {
                fprintf(stderr, ERROR_BAD_CHAR, tokens[i][0]);
                error = false;
            } else {
                fprintf(stderr, ERROR_BAD_STRING, tokens[i]);
                error = false;
            }
        }

        if (error) {
            stack_print();
            printf("\n");
        }

        stack_clear();
    }

    return 0;
}
