#include "shell.h"

/**
 * get_error - Handles error messages and status code for the shell.
 * @datash: Pointer to the data structure containing shell information.
 * @eval: The exit status code.
 *
 * Return: The exit status code.
 */
int get_error(data_shell *datash, int eval)
{
	char *error_message;

	switch (eval)
	{
		case -1:
			error_message = error_env(datash);
			break;
		case 126:
			error_message = error_path_126(datash);
			break;
		case 127:
			error_message = error_not_found(datash);
			break;
		case 2:
			if (_strcmp("exit", datash->args[0]) == 0)
				error_message = error_exit_shell(datash);
			else if (_strcmp("cd", datash->args[0]) == 0)
				error_message = error_get_cd(datash);
			break;
	}

	if (error_message)
	{
		write(STDERR_FILENO, error_message, _strlen(error_message));
		free(error_message);
	}

	datash->status = eval;
	return (eval);
}

