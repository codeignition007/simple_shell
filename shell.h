#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

/* command chaining mode */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN       3

/* conversion of characters */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* when 1, use getline() or strtok() */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* Read/write buffer function */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* history file name and max size */
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/* provides access to the environment variable of the current process */
extern char **environ;


/**
 * struct liststr - a singly_linked lists node for storing strings
 * @num: a declared variable for an integer
 * @str: an identifier for a string variable
 * @next: an identifier to the next node in a linked structure
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - A structure for passing information to a function
 * @arg: a parameter or argument that would pass into the getline function
 * @argv: a list of strings containing command line arguments
 * @path: a representation of files or directory path for current command
 * @argc: represents the total number of command line arguments
 * @line_count: represents the count of errors in a file
 * @err_num: a unique identifier for an error condition exit()s
 * @linecount_flag: when the flag is set, there will be counting of input lines
 * @fname: signifies the name or location of a file or path
 * @env: this linked list stores environment-related information within the program's runtime
 * @environ: this array provides access to the program's environment settings from LL env
 * @history: used to manage and store command history
 * @alias: used for managing and defining custom command shortcuts
 * @env_changed: a variable indicating changes to the program's environment when it's on
 * @status: it indicates the outcome or result of an operation (last executed command)
 * @cmd_buf: Represents the address of a pointer to cmd_buf, active during chaining
 * @cmd_buf_type: Variable representing the command type (e.g., CMD_type ||, &&, ;)
 * @readfd: File descriptor for reading inputted data
 * @histcount: Count or number related to command history
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - Data structure (struct) to define built-in commands
 * @type: a variable representing the type of a built-in command
 * @func: variable representing a function or method
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int bfree(void **);

/* atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_vars(info_t *);
int replace_alias(info_t *);
int replace_string(char **, char *);

/* lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* lists1.c */
list_t *node_starts_with(list_t *, char *, char);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
size_t get_node_index(list_t *, list_t *);

/* history.c */
char *get_history_file(info_t *info);
int read_history(info_t *info);
int write_history(info_t *info);
int renumber_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);

#endif
