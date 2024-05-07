/*
* Initializing a 3-dimensional array.
*/

#include <stdio.h>

int main(void) {
    /*
    * You can have as many dimensions as you want.
    */
    int a[2][2][2] = {
        {
            {0, 1},
            {2, 3},
        },
        {
            {4, 5},
            {6, 7},
        },
    };

    printf("%d\n", a[0][0][0]);
    printf("%d\n", a[0][0][1]);
    printf("%d\n", a[0][1][0]);
    printf("%d\n", a[0][1][1]);
    printf("%d\n", a[1][0][0]);
    printf("%d\n", a[1][0][1]);
    printf("%d\n", a[1][1][0]);
    printf("%d\n", a[1][1][1]);
    printf("\n");

    printf("%d\n", (int) sizeof(a));

    return 0;
}
