#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// We need to free() all memory that has been calloc()'ed.

int main(void) {
    // Allocate 10 bytes of memory.
    char *s = calloc(10, 1);
    //    ^--- Eventualy we'll need to free this pointer.

    // Copy "abc\0" into the memory.
    strncpy(s, "abc", 10);

    printf("%s\n", s);

    free(s);
    //   ^--- Pass the pointer that we originally got from calloc().

    return 0;
}
