#include <stdarg.h>
#include <unistd.h>

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int chars_printed = 0;

    while (*format != '\0') {
        if (*format == '%') {
            format++;

            if (*format == 'c') {
                char c = (char)va_arg(args, int);
                write(1, &c, 1);
                chars_printed++;
            } else if (*format == 's') {
                char *str = va_arg(args, char*);
                while (*str != '\0') {
                    write(1, str, 1);
                    str++;
                    chars_printed++;
                }
            } else if (*format == '%') {
                write(1, "%", 1);
                chars_printed++;
            }
        } else {
            write(1, format, 1);
            chars_printed++;
        }

        format++;
    }

    va_end(args);

    return chars_printed;
}

int main() {
    int count = _printf("Hello, %s! The character is %c and %% is for percent.\n", "world", 'A');
    printf("Total characters printed: %d\n", count);
    return 0;
}

