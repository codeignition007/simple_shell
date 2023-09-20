#include "shell.h"

/**
 * _custom_strncpy - Copies a string up to 'n' characters.
 * @dest: Destination buffer for the copied string.
 * @src: Source string to be copied.
 * @n: Maximum number of characters to copy.
 * Return: Pointer to the destination buffer.
 */
char *_custom_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * _custom_strncat - Concatenates two strings, up to 'n' characters.
 * @dest: Destination string where the concatenation occurs.
 * @src: Source string to be concatenated.
 * @n: Maximum number of characters to concatenate.
 * Return: Pointer to the destination string.
 */
char *_custom_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (result);
}

/**
 * _custom_strchr - Finds the first occurrence of a character in a string.
 * @s: Input string to search within.
 * @c: Character to search for.
 * Return: Pointer to the first occurrence of 'c' in 's', or NULL if not found.
 */
char *_custom_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

