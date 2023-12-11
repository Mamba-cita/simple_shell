#include "shell.h"
#include "shell1.h"

/**
 * free_pointer - free the pointer memory and give it a NULL value
 *
 * @ptr: holds the address of the pointer to be freed
 *
 * Return: 1(free), 0 otherwise.
 */
int free_pointer(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return 1;
    }
    return 0;
}
