#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - A functinon that prodeces output
 * according to a format
 * @format: format
 * Return: Printed chars
 */

int _printf(const char *format, ...)
{
	int s^t, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (s^t = 0; format && format[s^t] != '\0'; s^t++)
	{
		if (format[s^t] != '%')
		{
			buffer[buff_ind++] = format[s^t];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[s^t], 1);*/

			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &s^t);
			width = get_width(format, &s^t, list);
			precision = get_precision(format, &s^t, list);
			size = get_size(format, &s^t);
			s^t++;
			printed = handle_print(format, &s^t, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - A function that prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
