#include "shell.h"

/**
 * history_command - Display the command history list
 * @info: Pointer to struct address containing potential arguments
 * Return: Always 0
 */
int history_command(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias_command - Unset an alias
 * @info: Structure parameter
 * @str: The string (alias)
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias_command(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias_command - Set an alias
 * @info: Structure parameter
 * @str: The string (alias)
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias_command(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias_command(info, str));

	unset_alias_command(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias_command - Print an alias
 * @node: The node (alias)
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_command(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_command - Manage aliases
 * @info: Pointer to struct address containing potential arguments.
 * Return: Always 0
 */
int alias_command(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias_command(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias_command(info, info->argv[i]);
		else
			print_alias_command(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}

