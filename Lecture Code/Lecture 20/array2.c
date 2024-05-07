/*
* You can initialize all of the elements of an array.
*
* A multidimensional array in C is like a mathematical matrix:  the first
* dimension is the row; the second dimension is the column.
*/

#include <stdio.h>

int main(void) {
    /*
    * Declare and initialize a 2-row, 3-column array.
    */
    int a[2][3] = {
        {0, 1, 2},
        {3, 4, 5},
    };

#if 0
    /*
    * This initialization is incorrect:  The sizes a[2][3] represent
    * 2 rows and 3 columns, but the initialization is for 3 rows
    * end 2 columns.
    */
    int a[2][3] = {
        {0, 1},
        {2, 3},
        {4, 5}
    };
#endif

    printf("%d\n", a[0][0]);
    printf("%d\n", a[0][1]);
    printf("%d\n", a[0][2]);
    printf("%d\n", a[1][0]);
    printf("%d\n", a[1][1]);
    printf("%d\n", a[1][2]);
    printf("\n");

    printf("sizeof(a) is %d\n", (int) sizeof a);

    return 0;
}
