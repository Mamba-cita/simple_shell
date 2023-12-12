#include "shell.h"

/**
 * _strlen - returns length of given string to integer variable
 *
 * @s: the string length to be check.
 *
 * Return: the length/integer length of the string
 */
int _strlen(char *s)
{
	int index = 0;

	if (!s)
		return (0);

	while (*s++)
		index++;
	return (index);
}
