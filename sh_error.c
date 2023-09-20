#include "shell.h"

/**
 * print_error_str - Print an error string to stderr
 * @str: The error string to print
 *
 * Return: Nothing
 */
void print_error_str(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		print_error_char(str[i]);
		i++;
	}
}

/**
 * print_error_char - Write a character to stderr
 * @c: The character to write
 *
 * Return: Success (1).
 * Error, (-1) is returned, and errno is set
 */
int print_error_char(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * write_to_fd - Write a character to a file descriptor
 * @c: The character to write
 * @fd: The file descriptor to write to
 *
 * Return: Success (1).
 * Error, (-1) is returned, and errno is set
 */
int write_to_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * print_string_to_fd - Print a string to a file descriptor
 * @str: The string to print
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters written
 */
int print_string_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_to_fd(*str++, fd);
	}
	return (i);
}
