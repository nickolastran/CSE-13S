#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // Allocate 10 bytes of memory.
    char *s = calloc(10, 1);
    //         ^^^^^--- "allocate" memory
    //        ^-------- and "clear" (set all bytes to 0x00)

    // Safely copy "abc\0" into our new memory.
    strncpy(s, "abc", 10);
    // ^--- the "n" version of strcpy() is safer because it has buffer size

    printf("%s\n", s);

    return 0;
}
