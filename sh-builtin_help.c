#include "shell.h"

/**
 * aux_help - Display information about builtin commands.
 */
void aux_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDisplay brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_alias - Define or display aliases.
 */
void aux_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_cd - Change the shell working directory.
 */
void aux_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
}

