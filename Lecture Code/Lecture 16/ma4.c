#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A structure ("struct") contains a set of members.
// We use structs to keep members together for easy use.

// Declare a new type for our struct.
// Each struct of our type has three members, which we can set and access.
typedef struct {
    int i;
    char ch;
    double d;
} my_struct;

int main(void) {
    // Make a local variable "m" using our new struct type.
    my_struct m;

    // Copy values into the struct's members.
    m.i = 42;
    m.ch = '!';
    m.d = 3.14;

    printf("%d\n", m.i);
    printf("%c\n", m.ch);
    printf("%f\n", m.d);

    return 0;
}
