#include "shell.h"

/**
 * cd_shell - Change the current directory.
 * @datash: A pointer to the data_shell structure.
 * Return: Always returns 1 to continue shell execution.
 */
int cd_shell(data_shell *datash)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datash->args[1];
	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}
	/* If no directory provided, change to the home directory */
	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(datash);
		return (1);
	}
	/* Change to the previous directory */
	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datash);
		return (1);
	}
	/* Change to the current or parent directory */
	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}
	/* Change to the specified directory */
	cd_to(datash);
	return (1);
}
