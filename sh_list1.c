#include "shell.h"

/**
 * list_length - Get the length of a linked list.
 * @head: Pointer to the first node of the list.
 *
 * Return: The number of nodes in the list.
 */
size_t list_length(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}

	return (count);
}

/**
 * list_to_strings - Convert a linked list of strings to an array of strings.
 * @head: Pointer to the first node of the list.
 *
 * Return: An array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t list_size = list_length(head);
	size_t i;
	char **str_array;
	char *str;

	if (!head || list_size == 0)
		return (NULL);

	str_array = malloc(sizeof(char *) * (list_size + 1));

	if (!str_array)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);

		if (!str)
		{
			for (size_t j = 0; j < i; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		str_array[i] = str;
	}

	str_array[i] = NULL;
	return (str_array);
}

/**
 * print_list_contents - Print the contents of a linked list of nodes.
 * @head: Pointer to the first node of the list.
 *
 * Return: The number of nodes in the list.
 */
size_t print_list_contents(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}

	return (count);
}

/**
 * find_node_starts_with - Find the first node
 * whose string starts with a prefix.
 * @head: Pointer to the first node of the list.
 * @prefix: The prefix string to match.
 * @c: The next character after the prefix
 * to match (-1 if any character is allowed).
 *
 * Return: A pointer to the matching node or NULL if not found.
 */
list_t *find_node_starts_with(list_t *head, char *prefix, char c)
{
	char *p = NULL;

	while (head)
	{
		p = starts_with(head->str, prefix);

		if (p && ((c == -1) || (*p == c)))
			return (head);

		head = head->next;
	}

	return (NULL);
}

/**
 * get_node_index - Get the index of a node in a linked list.
 * @head: Pointer to the first node of the list.
 * @node: Pointer to the node whose index is to be found.
 *
 * Return: The index of the node or -1 if the node is not in the list.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);

		head = head->next;
		index++;
	}

	return (-1);
}

