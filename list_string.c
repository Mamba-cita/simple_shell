#include "shell.h"

/**
 * lists_to_string - give an array of strings
 *
 * @h: address of the pointer to the head node
 *
 * Return: ‘the array of strings of a singly list
 */
char **lists_to_string(list_t *h)
{
	list_t *ptr = h;
	size_t i = lists_len(h), j;
	char **strs;
	char *str1;

	if (!h || !i)
		return (NULL);
	str1 = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; ptr; ptr = ptr->next, i++)
	{
		str1 = malloc(_strlen(ptr->str1) + 1);
		if (!str1)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str1 = _strcpy(str1, ptr->str);
		strs[i] = str1;
	}
	strs[i] = NULL;
	return (strs);
}
