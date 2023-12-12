#include "shell.h"

/**
 * add_nodes - put a node at the start of the list
 *
 * @head: pointer to head node
 * @str: holds the string field of the nodes
 * @num: holds the index of the node used by history
 *
 * Return: the size of the singly list
 */
list_t *add_nodes(list_t **head, const char *str, int num)
{
	list_t *latest_head;

	if (!head)
		return (NULL);
	latest_head = malloc(sizeof(list_t));
	if (!latest_head)
		return (NULL);
	_memeset((void *)latest_head, 0, sizeof(list_t));
	latest_head->num = num;
	if (str)
	{
		latest_head->str = _strdupli(str);
		if (!latest_head->str)
		{
			free(latest_head);
			return (NULL);
		}
	}
	latest_head->next = *head;
	*head = latest_head;
	return (latest_head);
}

/**
 * add_nodes_end - put a node to the end of the singly list
 *
 * @head: pointer to head node
 * @str: holds the strrr field of the node
 * @num: holds the index of the node use by history
 *
 * Return: the size of the singly list
 */
list_t *add_nodes_end(list_t **head, const char *str, int num)
{
	list_t *curr_node, *ptr;

	if (!head)
		return (NULL);

	ptr = *head;
	curr_node = malloc(sizeof(list_t));
	if (!curr_node)
		return (NULL);
	_memeset((void *)curr_node, 0, sizeof(list_t));
	curr_node->num = num;
	if (str)
	{
		curr_node->str = _strdupli(str);
		if (!curr_node->str)
		{
			free(curr_node);
			return (NULL);
		}
	}
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = curr_node;
	}
	else
		*head = curr_node;
	return (curr_node);
}

/**
 * print_lists_str - print the str element of a singly linked list
 *
 * @h: address of pointer to the first node
 *
 * Return: the size of singly list
 */
size_t print_lists_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * del_nodes_at_index - remove the node at a given index
 *
 * @head: pointer to the first node
 * @index: holds the index of the node to remove
 *
 * Return: 1(SUCESS), or 0 (FAILURE)
 */
int del_nodes_at_index(list_t **head, unsigned int index)
{
	list_t *ptr, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		ptr = *head;
		*head = (*head)->next;
		free(ptr->str);
		free(ptr);
		return (1);
	}
	ptr = *head;
	while (ptr)
	{
		if (i == index)
		{
			prev_node->next = ptr->next;
			free(ptr->str);
			free(ptr);
			return (1);
		}
		i++;
		prev_node = ptr;
		ptr = ptr->next;
	}
	return (0);
}

/**
 * free_lists - empty all the nodes of a linked list
 *
 * @headd: pointer to head the node
 *
 * Return: void
 */
void free_lists(list_t **headd)
{
	list_t *curr_node, *next_node, *head;

	if (!headd || !*headd)
		return;
	head = *headd;
	curr_node = head;
	while (curr_node)
	{
		next_node = curr_node->next;
		free(curr_node->str);
		free(curr_node);
		curr_node = next_node;
	}
	*headd = NULL;
}
