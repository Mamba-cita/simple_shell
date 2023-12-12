#include "shell.h"

/**
 * is_cmds - check the file if it is an executable command
 * @info: the structure for the info
 * @path: the path pointing to the file
 *
 * Return: 1(true), 0 otherwise.
 */
int is_cmds(info_t *info, char *path)
{
	struct stat str;

	(void)info;
	if (!path || stat(path, &str))
		return (0);

	if (str.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupli_char - always duplicates the characters
 *
 * @pathstr: the path of the string.
 * @start: start the index
 * @stop: stop the index
 *
 * Return: address to the new buffer
 */
char *dupli_char(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buff[j++] = pathstr[i];
	buff[j] = 0;
	return (buff);
}

/**
 * check_path - check the command in the string path.
 *
 * @info: the structure info
 * @pathstr: the string path
 * @cmd: the cmd to find
 *
 * Return: full path(if found), otherwise (NULL)
 */
char *check_path(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, curr_position = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && start(cmd, "./"))
	{
		if (is_cmds(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dupli_char(pathstr, curr_position, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmds(info, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_position = j;
		}
		j++;
	}
	return (NULL);
}
