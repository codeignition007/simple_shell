#include "shell.h"

/**
 * get_sigint - Handles the SIGINT signal (Ctrl+C).
 * @sig: The signal number.
 *
 * This function is called when the SIGINT signal is received, typically when
 * the user presses Ctrl+C. It writes a message to the standard output.
 */
void get_sigint(int sig)
{
	(void)sig; /*  Unused parameter (prevents a warning) */
	write(STDOUT_FILENO, "\n^-^ ", 5);
	/* Writes a message to the standard output */
}

