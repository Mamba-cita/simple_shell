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

/**
 * _strcmp - compare two strings alphabetically.
 *
 * @s1: takes the first string
 * @s2: takes the second string
 *
 * Return: “-” (s1 < s2), “+”( s1 > s2), 0 (s1 == s2).
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * start - analyse if substring starts with the string searched.
 *
 * @haystack: hold the string to be searched.
 * @needle: hold the string to find
 *
 * Return: pointer of next char of the search string,
 * otherwise NULL.
 */
char *start(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - add the two strings.
 *
 * @dest: holds the target destination buf
 * @src: holds the buffer of the source
 *
 * Return: address to the target destination.
 */
char *_strcat(char *dest, char *src)
{
	char *ptr = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ptr);
}
