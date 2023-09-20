#include "shell.h"

/**
 * custom_memset - Fills a memory area with a constant byte.
 * @s: Pointer to the memory area to be filled.
 * @c: The byte to fill the memory with.
 * @n: The number of bytes to fill.
 *
 * Return: A pointer to the memory area s.
 */
char *custom_memset(char *s, char c, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = c;
	return (s);
}

/**
 * custom_free_strings - Frees an array of strings.
 * @str_array: The array of strings to be freed.
 */
void custom_free_strings(char **str_array)
{
	char **temp = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(temp);
}

/**
 * custom_realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous block of memory.
 * @old_size: The size of the previous block in bytes.
 * @new_size: The size of the new block in bytes.
 *
 * Return: A pointer to the newly allocated block of memory.
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
