#include "main.h"

void custom_print_buffer(char buff[], int *index);

/**
 * my_printf - My Printf function
 * @fmt: format.
 * Return: Printed characters.
 */
int my_printf(const char *fmt, ...)
{
	int i, printed = 0, total_printed = 0;
	int my_flags, my_width, my_precision, my_size, buff_index = 0;
	va_list arg_list;
	char my_buffer[BUFF_SIZE];

	if (fmt == NULL)
		return (-1);

	va_start(arg_list, fmt);

	for (i = 0; fmt && fmt[i] != '\0'; i++)
	{
		if (fmt[i] != '%')
		{
			my_buffer[buff_index++] = fmt[i];
			if (buff_index == BUFF_SIZE)
				custom_print_buffer(my_buffer, &buff_index);
			/* write(1, &fmt[i], 1);*/
			total_printed++;
		}
		else
		{
			custom_print_buffer(my_buffer, &buff_index);
			my_flags = get_my_flags(fmt, &i);
			my_width = get_my_width(fmt, &i, arg_list);
			my_precision = get_my_precision(fmt, &i, arg_list);
			my_size = get_my_size(fmt, &i);
			++i;
			printed = handle_my_print(fmt, &i, arg_list, my_buffer,
				my_flags, my_width, my_precision, my_size);
			if (printed == -1)
				return (-1);
			total_printed += printed;
		}
	}

	custom_print_buffer(my_buffer, &buff_index);

	va_end(arg_list);

	return (total_printed);
}

/**
 * custom_print_buffer - Prints the contents of the buffer if it exists
 * @buff: Array of characters
 * @buff_index: Index to add the next character, representing the length.
 */
void custom_print_buffer(char buff[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buff[0], *buff_index);

	*buff_index = 0;
}

