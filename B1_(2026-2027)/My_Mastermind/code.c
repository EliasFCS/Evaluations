#include "header.h"

int is_valid_code(const char *code)
{
    int index = 0;

    if (!code || my_strlen(code) != CODE_SIZE)
        return 0;

    while (index < CODE_SIZE) {
        if (code[index] < '0' || code[index] > '8')
            return 0;
        index++;
    }

    return 1;
}

char *generate_random_code(void)
{
    static char code[CODE_SIZE + 1];
    int count = 0;
    int index;
    int exists;
    char digit;

    srand((unsigned int)time(NULL));

    while (count < CODE_SIZE) {
        digit = VALID_PIECES[rand() % 9];
        exists = 0;
        index = 0;

        while (index < count) {
            if (code[index] == digit) {
                exists = 1;
                break;
            }
            index++;
        }

        if (!exists) {
            code[count] = digit;
            count++;
        }
    }

    code[CODE_SIZE] = '\0';
    return code;
}