#include "shell.h"

/**
 * restore_vars - change the vars in tokenized string
 *
 * @info: the structure parameter
 *
 * Return: 1 (if change), otherwise 0
 */
int restore_vars(info_t *info)
{
	list_t *node;
	int index = 0;

	for (index = 0; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
			continue;

		if (!_strcmp(info->argv[index], "$?"))
		{
			restore_string(&(info->argv[index]),
					_strdupli(convert_nums(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[index], "$$"))
		{
			restore_string(&(info->argv[index]),
					_strdupli(convert_nums(getpid(), 10, 0)));
			continue;
		}
		node = nodes_start_with(info->env, &info->argv[index][1], '=');
		if (node)
		{
			restore_string(&(info->argv[index]),
					_strdupli(_strcharr(node->str, '=') + 1));
			continue;
		}
		restore_string(&info->argv[index], _strdupli(""));

	}
	return (0);
}

/**
 * restore_string - changes/replaces the string
 *
 * @old: the old string address
 * @new: the new string
 *
 * Return: 1 (if changes), otherwise 0
 */
int restore_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
