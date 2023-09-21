#include "shell.h"

/**
 * exit_shell - Exits the shell program with the specified status code.
 *
 * @datash: The data_shell structure containing shell data.
 * Return: 0 on success, 1 on error.
 */
int exit_shell(data_shell *datash)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (datash->args[1] != NULL)
	{
		ustatus = _atoi(datash->args[1]);
		is_digit = _isdigit(datash->args[1]);
		str_len = _strlen(datash->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;

		/* Check if the argument is a valid non-negative integer. */
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(datash, 2);
			datash->status = 2; /* Set the exit status to 2 (error). */
			return (1); /* Return 1 to indicate an error. */
		}

		/* Set the exit status to the specified value modulo 256. */
		datash->status = (ustatus % 256);
	}

	return (0); /* Return 0 on success. */
}

