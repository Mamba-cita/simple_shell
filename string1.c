#include "shell.h"

/**
 * _strcpy - copies one string into another string
 *
 * @dest: the string destination
 * @src: the string source
 *
 * Return: address to the string destination
 */
char *_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = 0;
	return (dest);
}

/**
 * _strdupli - create a duplicate of the string.
 *
 * @str: string to be duplicated
 *
 * Return: address of the duplicated string
 */
char *_strdupli(const char *str)
{
	int len = 0;
	char *ptr;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	for (len++; len--;)
		ptr[len] = *--str;
	return (ptr);
}

/**
 * _puts - prints the inputed string to std-o.
 *
 * @str: take the string to be printed.
 *
 * Return: void
 */
void _puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * _putchar - print the character to std-o.
 *
 * @c: take the character to be printed.
 *
 * Return: 1 (Success), otherwise -1 (Error).
 */
int _putchar(char c)
{
	static char buf[WRITE_BUFF_SIZE];
	static int index;

	if (c == BUFF_FLUSH || index >= WRITE_BUFF_SIZE)
	{
		write(1, buf, index);
		index = 0;
	}
	if (c != BUFF_FLUSH)
		buf[index++] = c;
	return (1);
}
