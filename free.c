#include "shell.h"

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
