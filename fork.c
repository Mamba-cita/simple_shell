#include "linux.h"

/**
 * exec_cmd - a command using the execve system call
 * @full_path: The full path of the command to execute
 * @argv: The command-line arguments
 */
void exec_cmd(char *full_path, char **argv)
{
	if (execve(full_path, argv, NULL) < 0)
	{
		perror("execve");
		exit(1);
	}
}

/**
 * child_fork_wait - Fork a child process and wait for it to finish
 * @func: The function to execute in the child process
 */
void child_fork_wait(struct func *func)
{
	if (fork_func() == 0)
		run_func(func);
	else
		wait(0);
}
/**
 * get_cmd - Search for and execute a command in the PATH
 * @command_name: The command to search for
 * @argv: The arguments for the command
 *
 * Description: This function searches for the specified command in the PATH
 * and executes it if found. If the command is not found, it prints an error
 * message and exits with an error code.
 */

void get_cmd(char *command_name, char **argv)
{
	int command_number = 0;
	char *path_env = getenv("PATH");
	char *path = strdup(path_env);
	char *dir = strtok(path, ":");

	while (dir != NULL)
	{
		char full_path[1024];

		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command_name);

		if (access(full_path, X_OK) == 0)
		{
			exec_cmd(full_path, argv);
		}

		dir = strtok(NULL, ":");
	}

	fprintf(stdout, "sh: %d: %s: not found\n", ++command_number, command_name);
	exit(127); /*Command not found*/
}

/**
 * run_func - Final execution of the shell program
 * @func: The function to execute
 * Return : Does not return anything (void)
 */
void run_func(struct func *func)
{
	switch (func->type)
	{
	case EXEC:
	{
		struct execfunc *efunc = (struct execfunc *)func;

		if (efunc->argv[0] == 0)
			exit(1);
		if (strchr(efunc->argv[0], '/'))
			exec_cmd(efunc->argv[0], efunc->argv);
		else
			get_cmd(efunc->argv[0], efunc->argv);
		break;
	}
	case LIST:
	{
		struct col_list_func *lfunc = (struct col_list_func *)func;

		child_fork_wait(lfunc->left);
		child_fork_wait(lfunc->right);
		break;
	}
	case BACK:
	{
		struct revers_col *bfunc = (struct revers_col *)func;

		child_fork_wait(bfunc->func);
		break;
	}
	default:
		panicerror("run_func");
	}
	exit(0);
}
