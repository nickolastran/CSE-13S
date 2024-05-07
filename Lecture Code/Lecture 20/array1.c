/*
* Here's an example of initializing a multidimensional array.
*
* In lecture I had used {0}, but our recommended compiler options suggest
* using {{0}} because we are providing the value of one element of one row.
*
* If you provide a single value, then C will set the remaining values to 0.
*
* Example array a[][]:  You can initialize the entire array to all 0 by
*                       providing a single 0.
*
* Example array b[][]:  You can initialize one element to 1, and then the
*                       rest of the array will be set to 0.
*/

#include <stdio.h>

int main(void) {
    int a[2][2] = {{0}};  // initialize everything to 0
    int b[2][2] = {{1}};  // initialize b[0][0] = 1 and everything else to 0

    printf("%d\n", a[0][0]);
    printf("%d\n", a[0][1]);
    printf("%d\n", a[1][0]);
    printf("%d\n", a[1][1]);
    printf("\n");

    printf("%d\n", b[0][0]);
    printf("%d\n", b[0][1]);
    printf("%d\n", b[1][0]);
    printf("%d\n", b[1][1]);

    return 0;
}
