#include "shell.h"

/**
 * _free1 - free the pointer memory and give it a NULL value
 *
 * @ptr: holds the address of the pointer to  be free
 *
 * Return: 1(free), 0 otherwise .
 */
int _free1(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
