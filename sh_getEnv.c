#include "shell.h"

/**
 * get_environment_strings - Get environment strings as an array.
 * @info: Pointer to the info struct.
 * Return: Pointer to an array of environment strings.
 */
char **get_environment_strings(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_string_array(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_environment_variable - Unset an environment variable.
 * @info: Pointer to the info struct.
 * @variable: The name of the environment variable to unset.
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int unset_environment_variable(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * set_env_variable - Set a new environment variable or edit an existing one.
 * @info: Pointer to the info struct.
 * @variable: The name of the environment variable.
 * @value: The value to set for the environment variable.
 * Return: Always 0.
 */
int set_env_variable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

