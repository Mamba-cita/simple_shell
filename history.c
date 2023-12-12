#include "shell.h"

/**
 * gets_history_files - take the file history
 *
 * @info: the parameter of the structure
 *
 * Return: the string containing the file
 */

char *gets_history_files(info_t *info)
{
	char *buff, *dir;

	dir = _get_environ(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HEIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HEIST_FILE);
	return (buff);
}

/**
 * writes_history - make a new file, if exists add to existing file
 *
 * @info: the structure parameter.
 *
 * Return: 1 on success, else -1
 */
int writes_history(info_t *info)
{
	ssize_t fdd;
	char *filename = gets_history_files(info);
	list_t *curr_node = NULL;

	if (!filename)
		return (-1);

	fdd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdd == -1)
		return (-1);
	for (curr_node = info->history; curr_node; curr_node =
curr_node->next)
	{
		_putsfds(curr_node->str, fdd);
		_putfds('\n', fdd);
	}
	_putsfds(BUFF_FLUSH, fd);
	close(fdd);
	return (1);
}

/**
 * readd_history - read the file history
 *
 * @info: the parameter of the structure
 *
 * Return: history count(SUCCESS), 0 (FAILED)
 */
int readd_history(info_t *info)
{
	int i;
int last = 0, linecounts = 0;
	ssize_t fdd, rdlenght, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = gets_history_files(info);

	if (!filename)
		return (0);

	fdd = open(filename, O_RDONLY);
	free(filename);
	if (fdd == -1)
		return (0);
	if (!fstat(fdd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlenght = read(fdd, buff, fsize);
	buff[fsize] = 0;
	if (rdlenght <= 0)
		return (free(buff), 0);
	close(fdd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			built_history_list(info, buff + last, linecounts++);
			last = i + 1;
		}
	if (last != i)
		built_history_list(info, buff + last, linecounts++);
	free(buff);
	info->histcount = linecounts;
	while (info->histcount-- >= HEIST_MAX)
		del_nodes_at_index(&(info->history), 0);
	renum_history(info);
	return (info->histcount);
}
