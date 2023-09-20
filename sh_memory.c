#include "shell.h"

/**
 * free_and_null - Frees a pointer and sets it to NULL
 * @ptr: Pointer to the address of the pointer to free
 *
 * This function frees the memory pointed to by ptr and sets ptr to NULL.
 *
 * Return: 1 if the memory was freed, otherwise 0.
 */
int free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
