#include "main.h"

void custom_print_buf(char buff[], int *index);

/**
 * my_printf - My Printf function
 * @fmt: format.
 * Return: Printed characters.
 */
int my_printf(const char *fmt, ...)
{
	int i, chars_written = 0, total_written = 0;
	int my_flags, my_width, my_precision, my_size, buf_index = 0;
	va_list arg_list;
	char my_buf[BUFF_SIZE];

	if (fmt == NULL)
		return (-1);

	va_start(arg_list, fmt);

	for (i = 0; fmt && fmt[i] != '\0'; i++)
	{
		if (fmt[i] != '%')
		{
			my_buf[buf_index++] = fmt[i];
			if (buf_index == BUFF_SIZE)
				custom_print_buf(my_buf, &buf_index);
			chars_written++;
		}
		else
		{
			custom_print_buf(my_buf, &buf_index);
			++i;
			if (fmt[i] == 'd' || fmt[i] == 'i') {
				int num = va_arg(arg_list, int);
				chars_written = handle_int_print(my_buf, &buf_index, num);
				if (chars_written == -1)
					return (-1);
				total_written += chars_written;
			}
		}
	}

	custom_print_buf(my_buf, &buf_index);

	va_end(arg_list);

	return (total_written);
}

/**
 * custom_print_buf - Prints the contents of the buffer if it exists
 * @buff: Array of characters
 * @buf_index: Index to add the next character, representing the length.
 */
void custom_print_buf(char buff[], int *buf_index)
{
	if (*buf_index > 0)
		write(1, &buff[0], *buf_index);

	*buf_index = 0;
}

/**
 * handle_int_print - Handles printing of integer values
 * @buff: Buffer to store the formatted output
 * @buf_index: Pointer to the index in the buffer
 * @num: Integer to print
 * Return: Number of characters printed
 */
int handle_int_print(char buff[], int *buf_index, int num)
{
	int chars_printed = 0;
	if (num < 0) {
		buff[(*buf_index)++] = '-';
		num = -num;
		chars_printed++;
	}
	chars_printed += custom_itoa(&buff[*buf_index], num);
	*buf_index += chars_printed;
	return chars_printed;
}

/**
 * custom_itoa - Converts an integer to a string
 * @str: Buffer to store the resulting string
 * @num: Integer to convert
 * Return: Number of digits in the converted integer
 */
int custom_itoa(char *str, int num)
{
	int digits = 0;
	int temp = num;

	if (num == 0) {
		str[0] = '0';
		str[1] = '\0';
		return 1;
	}

	while (temp) {
		digits++;
		temp /= 10;
	}

	str[digits] = '\0';
	temp = num;

	while (digits--) {
		str[digits] = (temp % 10) + '0';
		temp /= 10;
	}

	return num < 0 ? digits + 2 : digits + 1;
}

