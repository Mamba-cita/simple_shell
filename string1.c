#include "shell.h"

/**
 * _strcpy - copies one string into another string
 *
 * @destination: the string destination
 * @source: the string source
 *
 * Return: address to the string destination
 */
char *_strcpy(char *destination, char *source)
{
    int index = 0;

    if (destination == source || source == NULL)
        return destination;
    while (source[index])
    {
        destination[index] = source[index];
        index++;
    }
    destination[index] = '\0';
    return destination;
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
    int length = 0;
    char *ptr;

    if (str == NULL)
        return NULL;
    while (*str++)
        length++;
    ptr = malloc(sizeof(char) * (length + 1));
    if (!ptr)
        return NULL;
    for (length++; length--;)
        ptr[length] = *--str;
    return ptr;
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
 * @character: take the character to be printed.
 *
 * Return: 1 (Success), otherwise -1 (Error).
 */
int _putchar(char character)
{
    static char buffer[WRITE_BUFF_SIZE];
    static int index;

    if (character == BUFF_FLUSH || index >= WRITE_BUFF_SIZE)
    {
        write(1, buffer, index);
        index = 0;
    }
    if (character != BUFF_FLUSH)
        buffer[index++] = character;
    return 1;
}
