#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// If we allocate something that is not an array, we'll need to use
// the * prefix operator to convert from the pointer to the thing that
// the pointer is pointing to.

int main(void) {
    // Allocate enough memory for one int.
    int *p = calloc(sizeof(int), 1);
    //  ^^--- The variable declaration reminds you that "*p" is an int.

    // Copy 42 into the new int.
    *p = 42;
//  ^--- Use * to convert the pointer p into the int that p points to.

    printf("%d\n", *p);
    //             ^--- Converting the pointer into the thing it points to.

    free(p);

    return 0;
}
