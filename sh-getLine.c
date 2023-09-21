#include "shell.h"

/**
 * read_line - Read a line of input from the user.
 *
 * @i_eof: Pointer to a variable that will be
 * set to 1 if end of file is reached.
 *           Set to 0 otherwise.
 *
 * Return: A pointer to the string containing the user input.
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}

