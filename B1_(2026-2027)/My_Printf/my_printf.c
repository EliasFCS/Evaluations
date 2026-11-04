#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>


int write_unsigned(unsigned long long n, int base, const char *digits) {
    int count = 0;
    
   
    if (n == 0) {
        if (write(1, &digits[0], 1) < 0) return -1;
        return 1;
    }

    if (n >= (unsigned long long)base) {
        int res = write_unsigned(n / base, base, digits);
        if (res < 0) return -1;
        count += res;
    }
    
    char c = digits[n % base];
    if (write(1, &c, 1) < 0) return -1;
    count++;
    
    return count;
}

int print_char(va_list *args) {
    char c = (char)va_arg(*args, int);
    if (write(1, &c, 1) < 0) return -1;
    return 1;
}

int print_str(va_list *args) {
    char *s = va_arg(*args, char *);
    if (!s) {
        s = "(null)";
    }
    int count = 0;
    while (s[count] != '\0') {
        if (write(1, &s[count], 1) < 0) return -1;
        count++;
    }
    return count;
}

int print_int(va_list *args) {
    int n = va_arg(*args, int);
    unsigned long long un;
    int count = 0;

    if (n < 0) {
        if (write(1, "-", 1) < 0) return -1;
        count++;
        
        un = (unsigned long long)(-(long long)n);
    } else {
        un = (unsigned long long)n;
    }
    
    int res = write_unsigned(un, 10, "0123456789");
    if (res < 0) return -1;
    
    return count + res;
}

int print_unsigned(va_list *args) {
    unsigned int n = va_arg(*args, unsigned int);
    return write_unsigned((unsigned long long)n, 10, "0123456789");
}

int print_octal(va_list *args) {
    unsigned int n = va_arg(*args, unsigned int);
    return write_unsigned((unsigned long long)n, 8, "0123456789");
}

int print_hex(va_list *args) {
    unsigned int n = va_arg(*args, unsigned int);
    return write_unsigned((unsigned long long)n, 16, "0123456789abcdef");
}

int print_pointer(va_list *args) {
    void *ptr = va_arg(*args, void *);
    uintptr_t addr = (uintptr_t)ptr;
    int count = 0;

    if (ptr == NULL) {
    
        char *null_str = "0x0";
        int i = 0;
        while (null_str[i] != '\0') {
            if (write(1, &null_str[i], 1) < 0) return -1;
            i++;
            count++;
        }
        return count;
    }

    if (write(1, "0x", 2) < 0) return -1;
    count += 2;

    int res = write_unsigned((unsigned long long)addr, 16, "0123456789abcdef");
    if (res < 0) return -1;
    
    return count + res;
}

int my_printf(char *restrict format, ...) {
    va_list args;
    va_start(args, format);
    int total_written = 0;
    int i = 0;

    if (!format) {
        va_end(args);
        return -1;
    }

    while (format[i] != '\0') {
        if (format[i] == '%') {
            i++;
            if (format[i] == '\0') {
                break;
            }
            int res = 0;
            if (format[i] == 'd' || format[i] == 'i') {
                res = print_int(&args);
            } else if (format[i] == 'u') {
                res = print_unsigned(&args);
            } else if (format[i] == 'o') {
                res = print_octal(&args);
            } else if (format[i] == 'x') {
                res = print_hex(&args);
            } else if (format[i] == 'c') {
                res = print_char(&args);
            } else if (format[i] == 's') {
                res = print_str(&args);
            } else if (format[i] == 'p') {
                res = print_pointer(&args);
            } else if (format[i] == '%') {
                char c = '%';
                res = write(1, &c, 1);
            } else {
                char c = format[i];
                res = write(1, &c, 1);
            }

            if (res < 0) {
                va_end(args);
                return -1;
            }
            total_written += res;
        } else {
            if (write(1, &format[i], 1) < 0) {
                va_end(args);
                return -1;
            }
            total_written++;
        }
        i++;
    }

    va_end(args);
    return total_written;
}