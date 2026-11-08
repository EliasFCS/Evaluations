#include "header.h"

int read_guess(char *buffer)
{
    char c;
    int length = 0;
    int overflow = 0;
    ssize_t bytes_read;

    while (1) {
        bytes_read = read(0, &c, 1);

        if (bytes_read <= 0)
            return 0;

        if (c == '\n')
            break;

        if (length < CODE_SIZE)
            buffer[length] = c;
        else
            overflow = 1;

        length++;
    }

    if (length != CODE_SIZE || overflow) {
        buffer[0] = '\0';
        return 1;
    }

    buffer[CODE_SIZE] = '\0';
    return 1;
}

void evaluate_guess(const char *secret, const char *guess,
    int *well_placed, int *misplaced)
{
    int used_secret[CODE_SIZE] = {0};
    int used_guess[CODE_SIZE] = {0};
    int guess_index = 0;
    int secret_index;

    *well_placed = 0;
    *misplaced = 0;

    while (guess_index < CODE_SIZE) {
        if (guess[guess_index] == secret[guess_index]) {
            (*well_placed)++;
            used_secret[guess_index] = 1;
            used_guess[guess_index] = 1;
        }
        guess_index++;
    }

    guess_index = 0;

    while (guess_index < CODE_SIZE) {
        if (!used_guess[guess_index]) {
            secret_index = 0;

            while (secret_index < CODE_SIZE) {
                if (!used_secret[secret_index]
                    && guess[guess_index] == secret[secret_index]) {
                    (*misplaced)++;
                    used_secret[secret_index] = 1;
                    break;
                }
                secret_index++;
            }
        }
        guess_index++;
    }
}