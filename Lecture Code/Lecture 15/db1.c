#include <math.h>
#include <stdio.h>

#ifdef DEBUG
const int enable_debug_printing = 1;
#else
const int enable_debug_printing = 0;
#endif

void debug(const char *s) {
    if (enable_debug_printing) {
        printf("%s\n", s);
    }
}

int main(void) {
    debug("I'm debugging!");
    return 0;
}
