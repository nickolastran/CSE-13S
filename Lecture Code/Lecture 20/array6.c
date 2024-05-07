/*
* You can skip the size of the first dimension.  It will be determined by
* the initialization data.  (All other dimensions must be provided.)
*
* You can use a creative #define to get the number of dimensions.
*/

#define DIMENSION_1 (sizeof(a) / sizeof(a[0]))
//                          ^           ^^^^------ one "slice" of array
//                          `--------------------- entire array
//                   ratio is number of "slices"

#include <stdio.h>

int main(void) {
    //   vv-------------- okay to omit the size of the first dimension
    int a[][3] = {
        { 0,  1,  2},
        { 3,  4,  5},
        { 6,  7,  8},
        { 9, 10, 11},
        {12, 13, 14},
        {15, 16, 17},   // Size of missing first dimension is determined by
        {18, 19, 20},   // the number of rows provided.
    };

    printf("DIMENSION_1 is %d\n", (int) DIMENSION_1);

    return 0;
}
