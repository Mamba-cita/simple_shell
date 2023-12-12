#include "shell.h"

/**
 * _memeset - fill the memory/buff with a constant bytes.
 *
 * @s: the address to the memory area.
 * @b: take the byte to fill with *s
 * @n: takes the amount of byte to be filled
 * Return: s (address to the memory area of s)
 */
char *_memeset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffrees - frees/empty a string that consist of strings
 *
 * @pp: takes the string of strings
 */
void ffrees(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _reallocc - reallocates a given blockof memory
 *
 * @ptr: take the address to previous allocated block of memory
 * @old_size: take the bytesize of the previous block.
 * @new_size: take the bytesize of the new block.
 *
 * Return: pointer to the deallocated block of memory.
 */
void *_reallocc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
