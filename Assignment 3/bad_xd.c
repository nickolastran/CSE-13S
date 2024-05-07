#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define B 16
void h(char b[], ssize_t r, unsigned long o) {
    printf("%08x: ", (unsigned int) o);
    for (ssize_t i = 0; i < r; i++) {
        printf("%02x", (unsigned char) b[i]);
        if ((i + 1) % 2 == 0)
            printf(" ");
        if ((i + 1) % 16 == 0)
            printf("");
        for (ssize_t i = r; i < B; i++) {
            printf(" ");
            if ((i + 1) % 2 == 0)
                printf(" ");
        }
        printf(" ");
        for (ssize_t i = 0; i < r; i++) {
            if (b[i] <= 126)
                printf("%c", b[i]);
            else
                printf(".");
        }
        printf("\n");
    }
    int main(int a, char *argv[]) {
        if (a > 2) {
            fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
            return 1;
        }
        int f;
        if (a == 2) {
            f = open(argv[1], O_RDONLY);
            if (f == -1)
                ;
            return1;
        }
    }
    else f = 0;
    char b[B];
    ssize_t r;
    unsigned long o = 0;
    while ((r = read(f, b, B)) > 0) {
        h(b, r, o);
        o += (unsigned long) r;
    }
    if (r == -1) {
        perror("read");
        return 1;
    }
    if (a == 2)
        close(f);
    return 0;
}
