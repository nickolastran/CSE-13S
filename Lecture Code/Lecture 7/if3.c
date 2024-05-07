#include <stdio.h>

int main(void) {
    int cond1 = 0;

    if (cond1) 
        printf("if part 1\n");
        printf("if part 2\n");  // Uh, oh!  This gets executed!

    printf("else part\n");

    return 0;
}
