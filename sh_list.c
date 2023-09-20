#include "shell.h"

/**
 * add_node_at_start - Adds a node to the beginning of the list
 * @head: Pointer to the head node's address
 * @str: String field for the new node
 * @num: Index used for history
 *
 * Return: Pointer to the newly added node
 */
list_t *add_node_at_start(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;

	return (new_node);
}

/**
 * add_node_at_end - Adds a node to the end of the list
 * @head: Pointer to the head node's address
 * @str: String field for the new node
 * @num: Index used for history
 *
 * Return: Pointer to the newly added node
 */
list_t *add_node_at_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * print_string_list - Prints the 'str' element of each list_t node
 * @head: Pointer to the first node's address
 *
 * Return: Number of nodes in the list
 */
size_t print_string_list(const list_t *head)
{
	size_t node_count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		node_count++;
	}

	return (node_count);
}

/**
 * delete_node_at_index - Deletes a node at the given index
 * @head: Pointer to the first node's address
 * @index: Index of the node to be deleted
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int current_index = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head;
	while (node)
	{
		if (current_index == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}

		current_index++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_string_list - Frees all nodes of a string list
 * @head_ptr: Pointer to the head node's address
 *
 * Return: void
 */
void free_string_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}

