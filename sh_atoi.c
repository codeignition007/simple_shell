#include "shell.h"

/**
 * is_interactive - Checks if the shell is in interactive mode.
 * @info: Pointer to the info struct.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int is_interactive(info_t *info)
{
	/* Check if stdin is a terminal and readfd is within valid limits. */
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 if c is a delimiter, 0 otherwise.
 */
int is_delimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * is_alpha - Checks if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to convert.
 *
 * Return: The converted integer if successful, 0 if no valid integer found.
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			output = output * 10 + (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	return (sign * output);
}

