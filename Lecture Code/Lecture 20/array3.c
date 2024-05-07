/*
* You can have more than 2 dimensions!
*/

#include <stdio.h>

int main(void) {
    /*
    * You can have as many dimensions as you want.
    */
    int a[2][2][2] = {{{0}}};  // initialize everything to 0

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
