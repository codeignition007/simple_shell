#include "shell.h"

/**
 * aux_help_env - Display help information for the 'env' command.
 */
void aux_help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Print the environment of the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_setenv - Display help information for the 'setenv' command.
 */
void aux_help_setenv(void)
{
	char *help = "setenv: setenv [name] [value] [replace]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Add or modify an environment variable.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_unsetenv - Display help information for the 'unsetenv' command.
 */
void aux_help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv [name]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Remove an environment variable.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_general - Display general help information.
 */
void aux_help_general(void)
{
	char *help = "^-^ shell, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "These cmds are defined internally. Type 'help' to see the list.\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Type 'help name' to find out more about a specific command.\n\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "  alias: alias [name=['string']]\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "  cd: cd [-L|-P [-e]] [-@] [dir]\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "  exit: exit [n]\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "  env: env [option] [name=value] [command [args]]\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "  setenv: setenv [variable] [value]\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "  unsetenv: unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_exit - Display help information for the 'exit' command.
 */
void aux_help_exit(void)
{
	char *help = "exit: exit [status]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Exit the shell with a specific status code.\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "If no status, the exit status will be that of the last cmd exec.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

