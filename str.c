#include <stdio.h>
#include <stdarg.h>
#include "max.h"
/**
str- prints strange letters after % in format
*@format: pointer to our string
*@i: index of character after %
*Return: count of putchar
*/
int str(const char *format, int i)
{
int count = 0;
if (format[i] != '%')
{
_putchar(format[i - 1]);
count += 1;
}
_putchar(format[i]);
count += 1;
return (count);
}
