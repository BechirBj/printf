#include <stdio.h>
#include <stdarg.h>
#include "max.h"
/**
 * _printf - prints anything
 * @F: pointer to string that contains specifiers
 * Return: number of characters printed
 **/
int _printf(const char *F, ...)
{
	unsigned int count = 0, i = 0;
	int (*f)(va_list);
	va_list list;

	if (F == '\0')
		return (-1);
	va_start(list, F);
	while (F && F[i])
	{
		if (F[i] != '%')
		{
			_putchar(F[i]);
			count++;
		}
		else if (F[i] == '%' && F[i + 1] == '\0')
			return (-1);
		else if (F[i] == '\0')
			return (count);
		else if (F[i] == '%')
		{
			f = getspecifier(F, i + 1);
			i += 1;
			if (f == NULL)
			{
				count += strange(F, i);
			}
			else
			{
				count = count + f(list);
				if (F[i] == '+' || F[i] == ' ' || F[i] == '#')
					i++;
			}
		}
		i++;
	}
	va_end(list);
	return (count);
}
