#include "shell.h"

/**
 * **_strtow - ignore repeated delimiters and split the string into words.
 *
 * @str: the string inputed.
 * @d: holds the delimiter string.
 *
 * Return: address to the arrays of strings, otherwise NULL
 */
char **_strtow(char *str, char *d)
{
    int j, b;
    int ind;
    int num, totalWords = 0;
    char **s;

    if (str == NULL || str[0] == 0)
        return NULL;
    if (!d)
        d = " ";
    for (ind = 0; str[ind] != '\0'; ind++)
        if (!is_deli(str[ind], d) && (is_deli(str[ind + 1], d) || !str[ind + 1]))
            totalWords++;

    if (totalWords == 0)
        return NULL;
    s = malloc((1 + totalWords) * sizeof(char *));
    if (!s)
        return NULL;

    for (ind = 0, j = 0; j < totalWords; j++)
    {
        while (is_deli(str[ind], d))
            ind++;
        b = 0;
        while (!is_deli(str[ind + b], d) && str[ind + b])
            b++;
        s[j] = malloc((b + 1) * sizeof(char));
        if (!s[j])
        {
            for (b = 0; b < j; b++)
                free(s[b]);
            free(s);
            return NULL;
        }
        for (num = 0; num < b; num++)
            s[j][num] = str[ind++];
        s[j][num] = 0;
    }
    s[j] = NULL;
    return s;
}

/**
 * **strtow2 - divide strings into words
 *
 * @str: the string inputed.
 * @d: the string delimeter.
 *
 * Return: address to the arrays of strings, otherwise NULL (on failure)
 */
char **strtow2(char *str, char d)
{
    int index;
    int j, b;
    int num, totalWords = 0;
    char **s;

    if (str == NULL || str[0] == 0)
        return NULL;
    for (index = 0; str[index] != '\0'; index++)
        if ((str[index] != d && str[index + 1] == d) ||
            (str[index] != d && !str[index + 1]) || str[index + 1] == d)
            totalWords++;
    if (totalWords == 0)
        return NULL;
    s = malloc((1 + totalWords) * sizeof(char *));
    if (!s)
        return NULL;
    for (index = 0, j = 0; j < totalWords; j++)
    {
        while (str[index] == d && str[index] != d)
            index++;
        b = 0;
        while (str[index + b] != d && str[index + b] && str[index + b] != d)
            b++;
        s[j] = malloc((b + 1) * sizeof(char));
        if (!s[j])
        {
            for (b = 0; b < j; b++)
                free(s[b]);
            free(s);
            return NULL;
        }
        for (num = 0; num < b; num++)
            s[j][num] = str[index++];
        s[j][num] = 0;
    }
    s[j] = NULL;
    return s;
}
