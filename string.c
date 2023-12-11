#include "shell.h"

/**
 * _strlen - returns length of given string to integer variable
 *
 * @str: the string length to be checked.
 *
 * Return: the length/integer length of the string
 */
int _strlen(char *str)
{
    int length = 0;

    if (!str)
        return 0;

    while (*str++)
        length++;
    return length;
}

/**
 * _strcmp - compare two strings alphabetically.
 *
 * @s1: takes the first string
 * @s2: takes the second string
 *
 * Return: “-” (s1 < s2), “+”( s1 > s2), 0 (s1 == s2).
 */
int _strcmp(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return *str1 - *str2;
        str1++;
        str2++;
    }
    return (*str1 == *str2) ? 0 : ((*str1 < *str2) ? -1 : 1);
}

/**
 * start - analyse if substring starts with the string searched.
 *
 * @mainStr: hold the string to be searched.
 * @subStr: hold the string to find
 *
 * Return: pointer of next char of the search string,
 * otherwise NULL.
 */
char *start(const char *mainStr, const char *subStr)
{
    while (*subStr)
        if (*subStr++ != *mainStr++)
            return NULL;
    return (char *)mainStr;
}

/**
 * _strcat - concatenate two strings.
 *
 * @dest: holds the target destination buffer
 * @src: holds the buffer of the source
 *
 * Return: address to the target destination.
 */
char *_strcat(char *destination, char *source)
{
    char *ptr = destination;

    while (*destination)
        destination++;
    while (*source)
        *destination++ = *source++;
    *destination = *source;
    return ptr;
}
