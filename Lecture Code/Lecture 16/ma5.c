#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// We can allocate memory for one of our new structs.

// Declare a new type.
typedef struct {
    int i;
    char ch;
    double d;
} my_struct;

int main(void) {
    // Allocate enough memory for one my_struct.
    my_struct *p = calloc(sizeof(my_struct), 1);

    // Copy values into the struct's members.
    // Method #1 (the next file's example has a better way).
    (*p).i = 42;
    (*p).ch = '!';
    (*p).d = 3.14;
//  ^^^^---- convert the pointer into a struct
//      ^--- use the . operator to access the members of the struct

    printf("%d\n", (*p).i);
    printf("%c\n", (*p).ch);
    printf("%f\n", (*p).d);

    free(p);

    return 0;
}
