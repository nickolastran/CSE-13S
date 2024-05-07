#include <stdio.h>

int main(void) {
    int i  = 0;

    while (i < 4) {
        printf("%d\n", i);
        i = i + 1;
    }

    int j  = 0;

    while (j < 8) {
        printf("b%d\n", j);
        j += 2;
    }

    int k  = 0;

    while (k < 4) {
        printf("c%d\n", k);
        k++;
    }

    return 0;
}
