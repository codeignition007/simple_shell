#include "shell.h"

/**
 * str_to_int - Convert a string to an integer
 * @s: The input string to convert
 * Return: The converted integer or -1 on error
 */
int str_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Print an error message
 * @info: Pointer to info struct containing information about the error
 * @error_msg: The error message to print
 */
void print_error(info_t *info, char *error_msg)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_msg);
}

/**
 * print_decimal - Print a decimal (integer) number to a file descriptor
 * @input: The integer to print
 * @fd: The file descriptor to write to
 * Return: The number of characters printed
 */
int print_decimal(int input, int fd)
{
	int (*output_char)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		output_char = _eputchar;
	if (input < 0)
	{
		absolute_value = -input;
		output_char('-');
		count++;
	}
	else
		absolute_value = input;
	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			output_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	output_char('0' + current);
	count++;

	return (count);
}

/**
 * convert_to_base - Convert a number to a specified base
 * @num: The number to convert
 * @base: The base to convert to
 * @flags: Conversion flags (e.g., CONVERT_UNSIGNED, CONVERT_LOWERCASE)
 * Return: The converted number as a string
 */
char *convert_to_base(long int num, int base, int flags)
{
	static char *digits;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	digits = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = digits[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comment - Replace the first '#' character with '\0'
 * @buf: The string to modify
 */
void remove_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

