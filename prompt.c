#include "shell.h"

/**
 * main - Entry point for the shell program
 * @agc: Number of arguments
 * @av: Array of strings containing the arguments
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */

int main(int agc, char **av)
{
	info_t info[] = { INFO_INIT };
	int fdd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fdd)
			: "r" (fdd));

	if (ac == 2)
	{
		fdd = open(av[1], O_RDONLY);
		if (fdd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_errputs(av[0]);
				_errputs(": 0: Can't open ");
				_errputs(av[1]);
				_errputchar('\n');
				_errputchar(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fdd;
	}
	populate_environ_list(info);
	_read_history(info);
	loop_hsh(info, av);
	return (EXIT_SUCCESS);
}
