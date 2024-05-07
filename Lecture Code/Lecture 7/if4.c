#include <stdio.h>

int main(void) {
    int cond1 = 0;

    if (cond1) printf("if part 1\n");

    printf("else part\n");

    for (;;) {
        printf("before\n");

        if (cond1) break;

        cond1 = 1;
        printf("after\n");
    }

    return 0;
}
