#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 16

void print_hex_ascii(char buffer[], ssize_t bytes_read, unsigned long offset) {
    printf("%08x: ", (unsigned int) offset);

    for (ssize_t i = 0; i < bytes_read; i++) {
        printf("%02x", (unsigned char) buffer[i]);
        if ((i + 1) % 2 == 0)
            printf(" ");
        if ((i + 1) % 16 == 0)
            printf("");
    }

    for (ssize_t i = bytes_read; i < BUFFER_SIZE; i++) {
        printf("  ");
        if ((i + 1) % 2 == 0)
            printf(" ");
    }
    printf(" ");

    for (ssize_t i = 0; i < bytes_read; i++) {
        if (buffer[i] >= 32 && buffer[i] <= 126) {
            printf("%c", buffer[i]);
        } else {
            printf(".");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return 1;
    }

    int file_desc;

    if (argc == 2) {
        file_desc = open(argv[1], O_RDONLY);
        if (file_desc == -1) {
            return 1;
        }
    } else {
        file_desc = STDIN_FILENO;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    unsigned long offset = 0;

    while ((bytes_read = read(file_desc, buffer, BUFFER_SIZE)) > 0) {
        print_hex_ascii(buffer, bytes_read, offset);
        offset += (unsigned long) bytes_read;
    }

    if (bytes_read == -1) {
        perror("read");
        return 1;
    }

    if (argc == 2) {
        close(file_desc);
    }

    return 0;
}
