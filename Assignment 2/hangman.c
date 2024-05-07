#include "hangman_helpers.h"

int main(int argc, char *argv[]) {
    char secret[MAX_LENGTH];
    char eliminated[MAX_LENGTH] = "";
    char guessed[MAX_LENGTH] = "";

    if (argc != 2) {
        return 1;
    }

    strncpy(secret, argv[1], strlen(argv[1]) + 1);
    if (validate_secret(secret) == false) {
        return 1;
    }

    char hangman[strlen(secret) + 1];
    int i;
    for (i = 0; (unsigned) i < strlen(secret); ++i) {
        if (secret[i] == '-') {
            hangman[i] = '-';
        } else if (secret[i] == ' ') {
            hangman[i] = ' ';
        } else if (secret[i] == '\'') {
            hangman[i] = '\'';
        } else {
            hangman[i] = '_';
        }
    }
    hangman[i] = '\0';

    if (string_contains_character(hangman, '_') == false) {
        printf("You win! The secret phrase was: %s", secret);
        return 0;
    }

    int counter = 0;
    while (counter < 6) {
        printf(CLEAR_SCREEN);
        printf("%s\n", arts[counter]);
        printf("\n");
        printf("    Phrase: %s\n", hangman);
        printf("Eliminated: %s\n", eliminated);
        printf("\n");

        char letter = read_letter();
        while (is_lowercase_letter(letter) == false
               || string_contains_character(guessed, letter) == true) {

            letter = read_letter();
        }

        if (string_contains_character(secret, letter) == true) {
            for (int i = 0; (unsigned) i < strlen(secret); ++i) {
                if (secret[i] == letter) {
                    hangman[i] = letter;
                }
            }
            strncat(guessed, &letter, 1);
        } else {
            strncat(guessed, &letter, 1);
            strncat(eliminated, &letter, 1);
            counter++;
        }

        int m = 0;
        int t = (int) strlen(eliminated);
        for (int j = 0; j < t - 1; j++) {
            for (int m = 0; m < t - j - 1; m++) {
                if (eliminated[m] > eliminated[m + 1]) {
                    char temp = eliminated[m];
                    eliminated[m] = eliminated[m + 1];
                    eliminated[m + 1] = temp;
                }
            }
        }

        if (string_contains_character(hangman, '_') == false) {
            printf(CLEAR_SCREEN);
            printf("%s\n", arts[counter]);
            printf("\n");
            printf("    Phrase: %s\n", secret);
            printf("Eliminated: %s\n", eliminated);
            printf("\n");
            printf("You win! The secret phrase was: %s\n", secret);
            return 0;
        }

        t = (int) strlen(eliminated);
        for (int j = 0; j < t - 1; j++) {
            if (eliminated[m] > eliminated[m + 1]) {
                char temp = eliminated[m];
                eliminated[m] = eliminated[m + 1];
                eliminated[m + 1] = temp;
            }
        }
    }
    printf("\033[1;1H\033[2J");
    printf("%s\n", arts[6]);
    printf("\n");
    printf("    Phrase: %s\n", hangman);
    printf("Eliminated: %s\n", eliminated);
    printf("\n");
    printf("You lose! The secret phrase was: %s\n", secret);
    return 0;
}
