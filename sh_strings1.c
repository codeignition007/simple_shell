#include "shell.h"

/**
 * string_copy - Copy a string from source to destination.
 * @dest: The destination address.
 * @src: The source address.
 *
 * Return: Pointer to the destination address.
 */
char *string_copy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * string_duplicate - Duplicate a string.
 * @str: The string to be duplicated.
 *
 * Return: Address of the duplicated string.
 */
char *string_duplicate(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}

/**
 * string_puts - Print a string to stdout.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void string_puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * string_putchar - Append a character to stdout.
 * @c: The character to be printed.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set.
 */
int string_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}
