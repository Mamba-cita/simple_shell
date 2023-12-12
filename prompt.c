#include "shell.h"

/**
 * main - Entry point for the shell program.
 * @argc: Number of arguments.
 * @argv: Array of strings containing the arguments.
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(int argc, char **argv)
{
    info_t info[] = { INFO_INIT };
    int fdd = 2;

    asm ("mov %1, %0\n\t"
            "add $3, %0"
            : "=r" (fdd)
            : "r" (fdd));

    if (argc == 2)
    {
        fdd = open(argv[1], O_RDONLY);
        if (fdd == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _errputs(argv[0]);
                _errputs(": 0: Can't open ");
                _errputs(argv[1]);
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
    loop_hsh(info, argv);
    return (EXIT_SUCCESS);
}
