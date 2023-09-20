#include "shell.h"

/**
  * is_executable - Check if a file is an executable command
  *  @info: Pointer to the info struct
  *  @path: Path to the file
  *
  * Return: 1 if the file is an executable command, 0 otherwise
  */
int is_executable(info_t *info, char *path)
{
	struct stat st;
	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
  * duplicate_chars - Duplicate characters from a string
  * @pathstr: The input string
  * @start: The starting index
  * @stop: The stopping index
  *
  * Return: Pointer to a new buffer containing the duplicated characters
  */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;
	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
  * find_executable_in_path - Find an executable command in the PATH
  * @info: Pointer to the info struct
  * @pathstr: The PATH string
  * @cmd: The command to be found
  *
  * Return: The complete path of the command if found, or NULL if not found
  */
char *find_executable_in_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;
	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_executable(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_executable(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
