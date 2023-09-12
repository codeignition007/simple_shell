#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <errno.h>

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - it contains pseudo-arguements so as to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: count the argument
 * @line_count: count the error
 * @err_num: the error code for exit()s
 * @linecount_flag: count this line of input if on
 * @fname: the program filename
 * @env: linked lists local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: alias node
 * @env_changed: turn on if environ was changed
 * @status: return status of the last exec'd command
 * @cmd_buf: address of pointers to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd read line input
 * @histcount: the line number count
 */
typedef struct passinfo
{
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
        char *arg;
	char *path;
	char *fname;
        char **argv;
        list_t *env;
	list_t *alias;
        list_t *history;
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
 * struct builtin - contain builtin string and function
 * @type: the builtin flags command
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_string.c */
int _strlen(char *);
char *starts_with(const char *, const char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_memory.c */
int bfree(void **);

/* toem_exits.c */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_atoi.c */
int interactive(info_t *);
int _isalpha(int);
int is_delim(char, char *);
int _atoi(char *);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_history.c */
char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int write_history(info_t *info);
int renumber_history(info_t *info);
int read_history(info_t *info);


/* toem_getinfo.c */
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);

/* toem_builtin1.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_lists1.c */
size_t list_len(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t print_list(const list_t *);
char **list_to_strings(list_t *);
size_t get_node_index(list_t *, list_t *);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_vars.c */
int replace_string(char **, char *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_vars(info_t *);
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *);

#endif
