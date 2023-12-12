#include "shell.h"

/**
 * loop_hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int loop_hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_the_info(info);
		if (interactives(info))
			_puts("$ ");
		_errputchar(BUFF_FLUSH);
		r = gets_inputs(info);
		if (r != -1)
		{
			set_the_info(info, av);
			builtin_ret = check_builtin(info);
			if (builtin_ret == -1)
				check_cmd(info);
		}
		else if (interactives(info))
			_putchar('\n');
		free_the_info(info, 0);
	}
	writes_history(info);
	free_the_info(info, 1);
	if (!interactives(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * check_builtin - checks for a builtin command
 *
 * @info: it return the structure info
 *
 * Return: -1 if builtin not found, 0 if builtin is executed successfully.
 */
int check_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _my_exits},
		{"env", _my_environ},
		{"help", _myhelpp},
		{"history", _myhistory},
		{"setenv", _myset_environ},
		{"unsetenv", _myunset_environ},
		{"cd", _my_cds},
		{"alias", _my_aliases},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * check_cmd - check for a command in PATH
 *
 * @info: return a info struct
 *
 * Return: void
 */
void check_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_deli(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = check_path(info, _get_environ(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		copy_cmd(info);
	}
	else
	{
		if ((interactives(info) || _get_environ(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmds(info, info->argv[0]))
			copy_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_erro(info, "not found\n");
		}
	}
}

/**
 * copy_cmd - copy the thread to run cmd
 * @info: return info struct
 *
 * Return: (void)
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environs(info)) == -1)
		{
			free_the_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_erro(info, "Permission denied\n");
		}
	}
}
