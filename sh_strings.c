#include "shell.h"

/**
 * str_len - Calculate the length of a string.
 * @str: The string to be measured.
 *
 * Return: The length of the string (integer).
 */
int str_len(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;

	return (length);
}

/**
 * str_cmp - Compare two strings.
 * @str1: Pointer to the first string.
 * @str2: Pointer to the second string.
 *
 * Return: 0 if the strings are equal, a positive value if str1 > str2,
 *         or a negative value if str1 < str2.
 */
int str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);

		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * str_starts_with - Check if a string starts with a given prefix.
 * @str: The string to be checked.
 * @prefix: The prefix to be searched.
 *
 * Return: A pointer to the character following the prefix in str if it starts
 *         with the prefix, or NULL otherwise.
 */
char *str_starts_with(const char *str, const char *prefix)
{
	while (*prefix)
	{
		if (*prefix++ != *str++)
			return (NULL);
	}

	return ((char *)str);
}

/**
 * str_concat - Concatenate two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the destination string.
 */
char *str_concat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;

	return (result);
}
