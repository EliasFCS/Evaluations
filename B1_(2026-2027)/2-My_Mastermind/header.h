#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#define CODE_SIZE 4
#define DEFAULT_ATTEMPTS 10
#define VALID_PIECES "012345678"

int my_strlen(const char *str);
int my_atoi(const char *str);
int is_valid_code(const char *code);
char *generate_random_code(void);

void evaluate_guess(const char *secret, const char *guess,
    int *well_placed, int *misplaced);

int read_guess(char *buffer);

#endif