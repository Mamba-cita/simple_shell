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
