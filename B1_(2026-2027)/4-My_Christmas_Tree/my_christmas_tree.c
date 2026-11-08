#include <unistd.h>
#include <stdlib.h>

void ft_putchar(char c) {
    write(1, &c, 1);
}

void print_line(int spaces, int stars, char c) {
    for (int i = 0; i < spaces; i++) {
        ft_putchar(' ');
    }
    for (int i = 0; i < stars; i++) {
        ft_putchar(c);
    }
    ft_putchar('\n');
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }
    
    int size = atoi(argv[1]);
    if (size <= 0) {
        return 0;
    }

    
    int current_start = 1;
    int last_rows = 0;
    for (int t = 0; t < size; t++) {
        last_rows = 4 + t;
        if (t + 1 < size) {
            current_start = current_start + 2 * last_rows - 4;
        }
    }
    int max_width = current_start + 2 * (last_rows - 1);

    
    current_start = 1;
    for (int t = 0; t < size; t++) {
        int rows = 4 + t;
        for (int r = 0; r < rows; r++) {
            int stars = current_start + 2 * r;
            int spaces = (max_width - stars) / 2;
            print_line(spaces, stars, '*');
        }
        if (t + 1 < size) {
            current_start = current_start + 2 * rows - 4;
        }
    }

    
    int trunk_width = (size % 2 == 0) ? size + 1 : size;
    for (int i = 0; i < size; i++) {
        int spaces = (max_width - trunk_width) / 2;
        print_line(spaces, trunk_width, '|');
    }

    return 0;
}