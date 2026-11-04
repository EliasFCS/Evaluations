#include "header.h"

int my_strlen(const char *str)
{
    int len = 0;

    while (str && str[len] != '\0')
        len++;

    return len;
}

int my_atoi(const char *str)
{
    int result = 0;
    int digit;
    int index = 0;

    if (!str || str[0] == '\0')
        return -1;

    while (str[index]) {
        if (str[index] < '0' || str[index] > '9')
            return -1;

        digit = str[index] - '0';

        if (result > (INT_MAX - digit) / 10)
            return -1;

        result = result * 10 + digit;
        index++;
    }

    return result;
}