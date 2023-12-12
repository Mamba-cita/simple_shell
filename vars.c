#include "shell.h"

/**
 * isa_chain - test the chain delimiter,
 * for the current char in the buffer.
 *
 * @info: the structure parameter.
 * @buf: the buffer for the character.
 * @p: position of the current address in the buffer.
 *
 * Return: 1( if chain delimeter), otherwise 0.
 */
int isa_chain(info_t *info, char *buf, size_t *p)
{
	size_t index = *p;

	if (buf[index] == '|' && buf[index + 1] == '|')
	{
		buf[index] = 0;
		index++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[index] == '&' && buf[index + 1] == '&')
	{
		buf[index] = 0;
		index++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[index] == ';')
	{
		buf[index] = 0;
		info->cmd_buf_type = CMD_CHIAN;
	}
	else
		return (0);
	*p = index;
	return (1);
}

/**
 * find_chain - decide if chaining,
 * should continue based on the last result.
 * @info: the structure parameter.
 * @buf: the buffer for character.
 * @p: position of the current address in the buffer.
 * @i: starting index in the buffer
 * @len: length of the buffer
 *
 * Return: (void)
 */
void find_chain(info_t *info, char *buf, size_t *p, size_t index, size_t len)
{
	size_t index = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			index = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			index = len;
		}
	}

	*p = index;
}

/**
 * restore_alias - rename an alias in the tokenized string
 *
 * @info: the structure parameter.
 *
 * Return: 1 (if rename), otherwise 0
 */
int restore_alias(info_t *info)
{
	list_t *node;
	int index;
	char *p;

	for (index = 0; index < 10; index++)
	{
		node = nodes_start_with(info->alias, info->argv[0], '=');
		if (!node)
		{
			return (0);
		}

		free(info->argv[0]);
		p = _strchar(node->str, '=');
		if (!p)
			return (0);
		p = _strdupli(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

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
