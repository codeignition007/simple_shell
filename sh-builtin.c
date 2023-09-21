#include "shell.h"

/**
 * get_builtin - Retrieves a pointer to the corresponding built-in function.
 * @cmd: The command to look up.
 *
 * Return: A function pointer to the corresponding built-in function, or NULL
 * if no match is found.
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },               /* Builtin command: env */
		{ "exit", exit_shell },        /* Builtin command: exit */
		{ "setenv", _setenv },         /* Builtin command: setenv */
		{ "unsetenv", _unsetenv },     /* Builtin command: unsetenv */
		{ "cd", cd_shell },            /* Builtin command: cd */
		{ "help", get_help },          /* Builtin command: help */
		{ NULL, NULL }
	};
	int i;

	/* Iterate through the built-in command array to find a match */
	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f); /* Return the corresponding function pointer */
}

