#include "header.h"

int main(int argc, char **argv)
{
    char *secret_code = NULL;
    int max_attempts = DEFAULT_ATTEMPTS;
    int attempt = 0;
    int well_placed;
    int misplaced;
    int argument_index = 1;
    int code_provided = 0;
    int attempts_provided = 0;
    char guess[CODE_SIZE + 1];

    while (argument_index < argc) {
        if (strcmp(argv[argument_index], "-c") == 0) {
            if (code_provided || argument_index + 1 >= argc) {
                printf("Error: invalid -c argument!\n");
                return 1;
            }
            secret_code = argv[argument_index + 1];
            if (!is_valid_code(secret_code)) {
                printf("Error: invalid secret code!\n");
                return 1;
            }
            code_provided = 1;
            argument_index += 2;
        } else if (strcmp(argv[argument_index], "-t") == 0) {
            if (attempts_provided || argument_index + 1 >= argc) {
                printf("Error: invalid -t argument!\n");
                return 1;
            }
            max_attempts = my_atoi(argv[argument_index + 1]);
            if (max_attempts <= 0) {
                printf("Error: invalid number of attempts!\n");
                return 1;
            }
            attempts_provided = 1;
            argument_index += 2;
        } else {
            printf("Error: unknown argument '%s'!\n", argv[argument_index]);
            return 1;
        }
    }

    if (!code_provided)
        secret_code = generate_random_code();

    if (!secret_code) {
        printf("Error: failed to generate secret code!\n");
        return 1;
    }

    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");

    while (attempt < max_attempts) {
        printf("---\n");
        printf("Round %d\n", attempt);

        while (1) {
            write(1, ">", 1);

            if (!read_guess(guess)) {
                write(1, "\n", 1);
                return 0;
            }

            if (!is_valid_code(guess)) {
                printf("Wrong input!\n");
                continue; 
            }
            break;
        }

        evaluate_guess(secret_code, guess, &well_placed, &misplaced);

        if (well_placed == CODE_SIZE) {
            printf("Congratz! You did it!\n");
            return 0;
        }

        printf("Well placed pieces: %d\n", well_placed);
        printf("Misplaced pieces: %d\n", misplaced);

        attempt++;
    }

    return 0;
}