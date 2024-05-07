#include <stdio.h>

int main(void) {
    int cond1 = 0;
    int cond2 = 0;

    if (cond1) {
        printf("if part\n");
    } else if (cond2) {
        printf("else if part\n");
    } else {
        printf("else part\n");
    }

    return 0;
}
