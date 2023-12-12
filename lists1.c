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
