#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    // Method #2 (better!).
    p->i = 42;
    p->ch = '!';
    p->d = 3.14;
//   ^^--- The "->" operator accesses a struct's member directly from a pointer
//  ^----- Pointer to a struct.
//     ^-- Member name.

    printf("%d\n", p->i);
    printf("%c\n", p->ch);
    printf("%f\n", p->d);

    free(p);

    return 0;
}
