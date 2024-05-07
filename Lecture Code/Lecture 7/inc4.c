#include <stdio.h>

int main(void) {
    int i = 1;

    while (i <= 64) {
        printf("%d\n", i);
        i *= 2;
    }

    return 0;
}
