#include "shell.h"

/**
 * _memeset - fill the memory/buff with a constant bytes.
 *
 * @buffer: the address to the memory area.
 * @byte: take the byte to fill with *buffer
 * @size: takes the amount of byte to be filled
 * Return: buffer (address to the memory area of buffer)
 */
char *_memeset(char *buffer, char byte, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++)
        buffer[i] = byte;
    return buffer;
}

/**
 * free_strings - frees/empty a string that consists of strings
 *
 * @string_array: takes the string of strings
 */
void free_strings(char **string_array)
{
    char **iterator = string_array;

    if (!string_array)
        return;
    while (*string_array)
        free(*string_array++);
    free(iterator);
}

/**
 * _reallocc - reallocates a given block of memory
 *
 * @ptr: take the address to the previously allocated block of memory
 * @old_size: take the byte size of the previous block.
 * @new_size: take the byte size of the new block.
 *
 * Return: pointer to the deallocated block of memory.
 */
void *_reallocc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;

    if (!ptr)
        return malloc(new_size);
    if (!new_size)
        return free(ptr), NULL;
    if (new_size == old_size)
        return ptr;

    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        new_ptr[old_size] = ((char *)ptr)[old_size];
    free(ptr);
    return new_ptr;
}
