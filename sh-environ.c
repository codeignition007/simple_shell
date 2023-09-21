#include "shell.h"

/**
 * cmp_env_name - Compares environment variable name with a given name.
 * @nenv: The environment variable string.
 * @name: The name to compare with.
 *
 * Return: The number of characters matched, or 0 if there's no match.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - Gets the value of an environment variable.
 * @name: The name of the environment variable to retrieve.
 * @_environ: The array of environment variables.
 *
 * Return: A pointer to the value of the environment variable,
 * or NULL if not found.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env to NULL */
	ptr_env = NULL;
	mov = 0;

	/* Loop through environment variables */
	for (i = 0; _environ[i]; i++)
	{
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - Prints the current environment variables.
 *
 * @datash: The data structure containing shell information.
 * Return: Always returns 1.
 */
int _env(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{
		/* Calculate the length of the environment variable */
		for (j = 0; datash->_environ[i][j]; j++)
			;

		/* Write the environment variable to standard output */
		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}

