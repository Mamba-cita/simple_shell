#include "shell.h"

/**
 * lists_len - check the length of the linked list
 *
 * @head: address of the pointer to the head node
 *
 * Return: the size of the singly list
 */
size_t lists_len(const list_t *head)
{
	size_t index = 0;

	while (head)
	{
		head = head->next;
		index++;
	}
	return (index);
}

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


/**
 * prints_lists - return all elements of a singly linked list
 *
 * @head: address of the pointer to the head node
 *
 * Return: the size of the singly linked list
 */
size_t prints_lists(const list_t *head)
{
	size_t index = 0;

	while (head)
	{
		_puts(convert_nums(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		index++;
	}
	return (index);
}

/**
 * nodes_start_with - prints node whose string starts with a prefix
 * @node: address of the pointer to the head node
 *
 * @prefix: holds the strings to match
 * @c: hold the next char after the prefix to match
 *
 * Return: the node that match, or NULL
 */
list_t *nodes_start_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = start(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_nodes_index - take the index of the node
 *
 * @head: address to the pointer to head node
 * @curr_ptr: pointer to the current node
 *
 * Return: the index of the node, otherwise -1
 */
ssize_t get_nodes_index(list_t *head, list_t *curr_ptr)
{
	size_t i = 0;

	while (head)
	{
		if (head == curr_ptr)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
