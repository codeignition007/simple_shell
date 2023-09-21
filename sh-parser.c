#include "shell.h"

/**
 * swap_char - Replaces specific characters in the input string.
 * @input: The input string to modify.
 * @bool: Flag indicating the direction of character replacement.
 *
 * Return: The modified input string.
 */
char *swap_char(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16; /* Replace '|' with '16'. */
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12; /* Replace '&' with '12'. */
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]); /* Restore '|' character. */
			input[i] = (input[i] == 12 ? '&' : input[i]); /* Restore '&' character. */
		}
	}
	return (input);
}

/**
 * add_nodes - Adds separator and line nodes to respective linked lists.
 * @head_s: Pointer to the separator linked list.
 * @head_l: Pointer to the line linked list.
 * @input: The input string to process and split.
 *
 * This function processes the input string,
 * identifies separators (';', '|', '&'),
 * and splits it into separate lines accordingly. It modifies the input string.
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = swap_char(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * go_next - Advances the separator and line linked list pointers.
 * @list_s: Pointer to the separator linked list.
 * @list_l: Pointer to the line linked list.
 * @datash: Pointer to the data_shell structure.
 *
 * This function advances the separator
 * and line linked list pointers according to
 * the command execution status and the type of separator encountered.
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - Splits and executes commands from the line linked list.
 * @datash: Pointer to the data_shell structure.
 * @input: The input string to process.
 *
 * This function splits the input string
 * into separate commands using the separator
 * linked list and executes each command.
 *
 * Return: 0 if no more commands to execute, 1 otherwise.
 */
int split_commands(data_shell *datash, char *input)
{
	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - Splits the input line into tokens.
 * @input: The input line to split.
 *
 * Return: An array of tokens.
 *
 * This function splits the input line into an array of tokens based on the
 * specified delimiter characters.
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}

