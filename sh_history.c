#include "shell.h"

/**
 * get_history_filepath - Get the history file path
 * @info: Pointer to the parameter struct
 *
 * Return: Allocated string containing the history file path
 */
char *get_history_filepath(info_t *info)
{
	char *home_dir, *history_path;

	home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return (NULL);

	history_path = malloc(sizeof(char) *
			(_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!history_path)
		return (NULL);

	history_path[0] = '\0';
	_strcpy(history_path, home_dir);
	_strcat(history_path, "/");
	_strcat(history_path, HIST_FILE);

	return (history_path);
}

/**
 * write_history_entry - Write a single history entry to a file descriptor
 * @fd: File descriptor to write to
 * @entry: History entry to write
 *
 * Return: 1 on success, -1 on failure
 */
static int write_history_entry(int fd, const char *entry)
{
	if (_putsfd(entry, fd) == -1)
		return (-1);

	if (_putfd('\n', fd) == -1)
		return (-1);

	return (1);
}

/**
 * write_history_to_file - Write command history to a file
 * @info: Pointer to the parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int write_history_to_file(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_filepath(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		if (write_history_entry(fd, node->str) == -1)
		{
			close(fd);
			return (-1);
		}
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/* ... (continued) */

/**
 * renumber_history_entries - Renumber the history entries
 * @info: Pointer to struct containing potential arguments
 *
 * Return: Number of history entries
 */
int renumber_history_entries(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}

