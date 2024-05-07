#include "hangman_helpers.h"

bool is_lowercase_letter(char c) {
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    return false;
}

bool validate_secret(const char *secret) {
    if (strlen(secret) > MAX_LENGTH) {
        printf("the secret phrase is over 256 characters\n");
        return false;
    }
    for (int i = 0; (unsigned) i < strlen(secret); ++i) {
        char c = secret[i];
        if (is_lowercase_letter(c) == false && c != ' ' && c != '\'' && c != '-') {
            printf("invalid character: '%c'\n", c);
            printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                   "apostrophes\n");
            return false;
        }
    }
    return true;
}

bool string_contains_character(const char *s, char c) {
    while (*s) {
        if (*s == c) {
            return true;
        }
        s++;
    }
    return false;
}

char read_letter(void) {
    char guess = '\0';
    printf("Guess a letter: ");
    int c;
    while ((c = getchar()) != '\n') {
        if (guess == EOF) {
        } else {
            guess = (char) c;
        }
    }
    return guess;
}
