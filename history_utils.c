#include "shell.h"

/**
 * built_history_list - append a entry to linked list history
 *
 * @info: used to maintain struct containing potential arguments.
 * @buff: the buffer to store the history
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int built_history_list(info_t *info, char *buff, int linecount)
{
	list_t *ptr = NULL;

	if (info->history)
		ptr = info->history;
	add_nodes_end(&ptr, buff, linecount);

	if (!info->history)
		info->history = ptr;
	return (0);
}

/**
 * renum_history - renumber the linked list history after every changes.
 *
 * @info: used to maintain the struct containing potential arguments
 *
 * Return: the latest history count
 */
int renum_history(info_t *info)
{
	list_t *ptr = info->history;
	int i = 0;

	while (ptr)
	{
		ptr->num = i++;
		ptr = ptr->next;
	}
	return (info->histcount = i);
}
