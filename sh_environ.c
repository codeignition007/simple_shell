#include "shell.h"

/**
 * my_env - Display the current environment.
 * @info: Pointer to a struct containing potential arguments.
 * Return: Always 0.
 */
int my_env(info_t *info)
{
	/* Print the list of environment variables */
	print_list_str(info->env);
	return (0);
}

/**
 * get_env - Get the value of an environment variable.
 * @info: Pointer to a struct containing potential arguments.
 * @name: Name of the environment variable.
 * Return: The value of the variable or NULL if not found.
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - Set a new environment variable or update an existing one.
 * @info: Pointer to a struct containing potential arguments.
 * Return: Always 0.
 */
int my_setenv(info_t *info)
{
	/* Check the number of arguments */
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	/* Set the environment variable */
	if (my_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Unset one or more environment variables.
 * @info: Pointer to a struct containing potential arguments.
 * Return: Always 0.
 */
int my_unsetenv(info_t *info)
{
	int i;

	/* Check the number of arguments */
	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	/* Unset the specified environment variables */
	for (i = 1; i <= info->argc; i++)
		my_unsetenv(info, info->argv[i]);
	return (0);
}

/**
 * populate_env_list - Populate the environment linked list.
 * @info: Pointer to a struct containing potential arguments.
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	/* Copy the environment variables to a linked list */
	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

